/*********************************************************************
 *		
 *  ��      ��:    ObjectMap.h   		Freezeӳ�������
 *
 *  ��Ȩ����:   Shanghai Baosight Software Co., Ltd.
 *
 *  ����������ָ���ļ����ͣ�ֵ���ͺ�ӳ������͹�������ӳ�������
 *
 *  �汾��ʷ		
 *      1.0    2012-02-02    Haykin-2010    //TODO����ӱ�����Ҫ�޸�����
 *      1.1	 2012-02-02	  Haykin-2010    ���linux�����쳣����
*********************************************************************/
#ifndef __PACE_OBJECTMAP_H__
#define __PACE_OBJECTMAP_H__

#include <pace/Component.h>
#include <IceUtil/IceUtil.h>
#include <IceUtil/Monitor.h>
#include <IceUtil/Mutex.h>
#include <IceUtil/Thread.h>
#include <list>


namespace iPlature
{
/**
 * Freezeӳ������ݿ�ķ��ʰ�װ��
 * 
 * @see Freeze::Map 
 * ӳ�������
 * һ��ӳ���MapType������Freeze::Mapģ�����ʵ��������,ObjectMap�Ӷ�Ӧ��MapType�̳У�
 * ���ObjectMap��������Freeze::MapΪ�����ṩ�����Ͷ���ͷ���,Freeze::Map��Ҫ������������:
 * 1.iterator begin()
 * 3.iterator end()
 * 2.const_iterator begin() const
 * 4.const_iterator end() const
 * 5.bool empty() const �Ƿ�Ϊ��?
 * 6.size_type size() const map��С
 * 7.size_type max_size() const   ������:0xffffffff
 * 8.iterator insert(iterator position, const value_type& key) ��positionǰ����
 * 9.std::pair<iterator, bool> insert(const value_type& key) ���룬���ض�Ӧ�����Ӻ�״̬
 * 10.void put(const value_type& key) ����
 * 11.void erase(iterator position) ɾ����Ӧλ�ü�¼
 * 12.size_type erase(const key_type& key) ����ɾ��
 * 13.void erase(iterator first, iterator last) ��firstɾ����last
 * 14.void clear() ���
 * 15.void destroy() ���
 * 16.const_iterator find(const key_type& key) const ��������
 * 17.size_type count(const key_type& key) const ��������
 * 18.const Ice::CommunicatorPtr& communicator() const ���ض�Ӧcommunicator
 * 
 */
template<class Map>
struct __Map_Traits{};

template<typename keytype, typename mappedtype, 
class KeyCodec, class ValueCodec,class Compare>
struct __Map_Traits< Freeze::Map<keytype,mappedtype,KeyCodec,ValueCodec,Compare> >
{
	typedef KeyCodec TheKey;
	typedef ValueCodec TheValue;

	typedef keytype key_type;
	typedef mappedtype mapped_type;					//2012-2-2

	typedef std::pair<key_type,mapped_type> value_type;
};

template<class Map,class MapTraits=__Map_Traits<Map> >
class ObjectMapWriter : public IceUtil::Thread
{
public:
	typedef typename MapTraits::value_type value_type;
	typedef typename MapTraits::key_type key_type;
	typedef typename MapTraits::mapped_type mapped_type;
    typedef typename Map::size_type size_type;

    enum Action {INSERT=0x1,CLEAR=0x2,ERASE=0x3,UNKOWN=0x99};
    template <typename K,typename V> 
    struct Item
    {
       Action action;
       K key;
       V value;
	   Item():action(UNKOWN),key(K()),value(V()){}
	   ~Item(){}
	   const Item& operator=(const Item& rsh){action=rsh.action;key=rsh.key;value=rsh.value;return *this;}
    };
    typedef Item<key_type,mapped_type> ItemType;
    typedef std::list<ItemType> ItemList;
    typedef IceUtil::Monitor<IceUtil::Mutex> Monitor;

    ObjectMapWriter(Map& m):_map(m),_running(false){}

    virtual ~ObjectMapWriter(){}
    
    virtual void run()
    {
            _running = true;
            while(_running)
            {
               ItemType item = next();
               if(!_running) break; 
               try{
                 switch (item.action)
                 {
                       case INSERT:
                               _map.put(std::make_pair(item.key,item.value));
                               {   //write completed,release cache
                                   Monitor::Lock sync(_monitor);
                                   _cache.erase(item.key);
                               }
                               break;
                       case CLEAR:
                               _map.clear();
                               break;
                       case ERASE:
                               _map.erase(item.key);
                               break;
                       default:break;
                 }
               }
               catch(...)
               {
                  //just ignore any exception here.
               }
            }//while
    }

    void insert(const value_type& v)
    {
        ItemType item;
        item.action = INSERT;
        item.key = v.first;
        item.value = v.second;
        put(item);
    }
    void clear()
    {
        ItemType item;
        item.action = CLEAR;
        put(item); 
    }
    void erase(const key_type& k)
    {
        ItemType item;
        item.action = ERASE;
        item.key = k;
        put(item);
    }
    bool getInCache(const key_type& k,mapped_type& v)
    {
        Monitor::Lock sync(_monitor);
        bool found = false;
        if(_cache.find(k) != _cache.end())
        {
           v = _cache[k];
           found = true;
        }
        return found;
    }
    void stop()
    {
       Monitor::Lock sync(_monitor);
       _running = false;
       _monitor.notify();
    }
private:
   void put(const ItemType& item)
   {
       Monitor::Lock sync(_monitor);
       switch(item.action)
       {
       case INSERT:  _cache[item.key] = item.value;break;
       case ERASE :  _cache.erase(item.key);break;
       case CLEAR :  _cache.clear();break;
       default:break;
       }
       _queue.push_back(item);
       if(_queue.size() == 1)
       {
           _monitor.notify();
       }       
   }
   ItemType next()
   {
      ItemType item;
      Monitor::Lock sync(_monitor);
      while(_queue.empty())
      {
         if(!_running) return item;
         _monitor.wait();
      }
      item = _queue.front();
      _queue.pop_front();
      return item;
   } 
   Map _map;
   Monitor      _monitor;
   ItemList  _queue;
   std::map<key_type,mapped_type> _cache;
   bool _running;
};

template<class Map,bool Cached=false,class MapTraits=__Map_Traits<Map> >
class ObjectMap : public Map,public IceUtil::AbstractMutexI<IceUtil::RecMutex>
{
public:
    typedef typename MapTraits::TheKey TheKey;
    typedef typename MapTraits::TheValue TheValue;

    typedef typename MapTraits::value_type value_type;
	typedef typename MapTraits::key_type key_type;
	typedef typename MapTraits::mapped_type mapped_type;

    typedef typename Map::size_type size_type;
    typedef typename Map::iterator iterator;
    typedef typename Map::const_iterator const_iterator;
    /**
     *
     */
    static Freeze::ConnectionPtr createConnection(const std::string& map)
    {
        return Component::instance()->createFreezeConnection(map);
    }
    /**
     *
     */
    ObjectMap(const std::string& map)
      :Map(Component::instance()->createFreezeConnection(map),
                map+".map")
    {
       //Component::instance()->updateDBInfo(map,
       //                                    Component::instance()->getDBEnv(map),
       //                                    map+".map",
       //                                    "map",
       //                                    TheKey::typeId(),
       //                                    TheValue::typeId());
       if(Cached)
       {
          Map m(Component::instance()->createFreezeConnection(map),map+".map");
          _writer = new ObjectMapWriter<Map>(m); 
          _writer->start();
       }
    }
    /**
     *
     */
    ObjectMap(const std::string& map,const Freeze::ConnectionPtr& conn)
      :Map(conn,map+".map")
      ,_conn(conn)
    {
       //Component::instance()->updateDBInfo(map,
       //                                    Component::instance()->getDBEnv(map),
       //                                    map+".map",
       //                                    "map",
       //                                    TheKey::typeId(),
       //                                    TheValue::typeId());
       if(Cached)
       {
          Map m(Component::instance()->createFreezeConnection(map),map+".map");
          _writer = new ObjectMapWriter<Map>(m); 
          _writer->start();
       }
    }
    /**
     *
     */
    void commit(){
       if(_trans)
       {
         _trans->commit();
         _trans = 0;
       }
    }
    /**
     *
     */
    void rollback() {
       if(_trans)
       {
         _trans->rollback();
         _trans = 0;
       }
    }
    /**
     *
     */
    void beginTransaction(){
       if(_conn && !_trans)
       {
          _trans = _conn->beginTransaction();
       }
    }
    void put(const value_type& kv)
    {
       if(_writer)
       {
          _writer->insert(kv);
       }  
       else
       {
          Map::put(kv);
       }
    }
    void clear()
    {
       if(_writer)
       {
          _writer->clear();
       }
       else
       {
          Map::clear();
       }
    }
    void erase(iterator pos)
    {
		if(_writer)
		{
			_writer->erase((*pos).first);
		}
		else
		{
			Map::erase(pos);
		}
    }
    void erase(iterator first,iterator last)
    {
		if(_writer)
		{
			for (iterator pos=first;pos!=last;++pos)
			{
				_writer->erase((*pos).first);
			}
		}
		else
		{
			Map::erase(first,last);
		}       
    }
    size_type erase(const key_type& key)
    {
       if(_writer)
       {
          _writer->erase(key);
          return 1;//async call ,so we just assume it succeed forever.
       }
       return Map::erase(key);
    }
    bool cache(const key_type& k,mapped_type& v) const
    {
       if(_writer)
       {
          return _writer->getInCache(k,v);
       } 
       return false;
    }
private:
    Freeze::ConnectionPtr _conn;
    Freeze::TransactionPtr _trans;
    IceUtil::Handle< ObjectMapWriter<Map> > _writer;
};

}

#endif

