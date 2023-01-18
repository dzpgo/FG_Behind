/*********************************************************************
 *		
 *  文      件:    HMIControl.h   		//控件类头文件
 *
 *  版权所有:   Shanghai Baosight Software Co., Ltd.
 *
 *  概述：//HMIControl控件基本类
 *        ：//TODO
 *        ：//TODO
 *
 *  版本历史		
 *      1.0    2010-10-14    Haykin-2010    //TODO请添加本次主要修改内容
 *      %USER%   
*********************************************************************/
/****************************************************************************************
HMIComBox	:　value=Name=S64,Text=S100,List=[Item=S100],BackColor=I4,ForeColor=I4
HMILable			:    value=Name=S64,Text=S100,BackColor=I4,ForeColor=I4
HMIImageBox : value=Name=S64,Visable=I4
*****************************************************************************************/
#pragma once
#include <pace/SmartData.h>
#include <vector>
#include <string>
#include <pace/Simple_cast.h>
#include <pace/InvalidValue.h>
namespace iPlature
{
	class SmartItemParser
	{
	public:
		typedef vector<pair<string, int> > VC_ITEM_INFO;
		static void Parse(const string& strItem, VC_ITEM_INFO& vcItem);
	};

	/*********************************************************************************************/
	/*														HMIColor																			*/
	/**********************************************************************************************/
	typedef enum
	{
		HMI_COLOR_DEFAULT = 0
		, HMI_COLOR_BLACK =-16777216
		, HMI_COLOR_BLURE = -16776961
		, HMI_COLOR_CORAL = -32944
		, HMI_COLOR_CRIMSON = -2354116
		, HMI_COLOR_CYAN = -16711681
		, HMI_COLOR_GRAY = -8355712
		, HMI_COLOR_GREEN = -16744448
		, HMI_COLOR_MAGENTA = -65281
		, HMI_COLOR_RED = -65536
		, HMI_COLOR_SALMON = -360334
		, HMI_COLOR_SILVER = -4144960
		, HMI_COLOR_TAN = -2968436
		, HMI_COLOR_WHITE = -1
		, HMI_COLOR_YELLOW = -256
		, HMI_COLOR_YELLOWGREEN = -6632142
		, HMI_COLOR_ORANGE = -23296
	} HMI_COLOR;

/*********************************************************************************************/
/*														HMIControl																			*/
/**********************************************************************************************/
	class HMIControl
	{
	public:
		HMIControl(const SmartData& sd);
		HMIControl(const string& strName);
		HMIControl(const SmartData& sd, const std::string& serverKey);
		HMIControl(const string& strName, const std::string& serverKey);
		virtual ~HMIControl(void);

		SmartData& operator [](const char*);

		void AddItem(const string& strItem, const SmartData& sd);

		void SetItem(const string& strItem, const SmartData& sd);

		SmartData GenItem(const string& strItem, int nSize);

		

		virtual SmartData& GetData();

		const string GetName() const;

		bool IsRefresh() const;
		void SetRefresh(bool bRefresh);

		const HMIControl& operator = (const HMIControl& ctl);



		virtual void UpdateControl(const SmartData& sd);

	private:
		SmartData createItem(SmartData& sd);

		SmartData& createChildItem(const SmartItemParser::VC_ITEM_INFO& vc, int n, SmartData& parentSd, SmartData& parentTypSd);

		void InitData();
	
	protected:
		SmartData _sd;
		SmartData _sdTyp;
		bool _bRefresh;
	};



	inline const string HMIControl::GetName() const
	{
		return _sd.name();
	}

	inline bool HMIControl::IsRefresh() const
	{
		return _bRefresh;
	}

	inline void HMIControl::SetRefresh(bool bRefresh)
	{
		_bRefresh = bRefresh;
	}




	/*********************************************************************************************/
	/*														HMIColorControl																*/
	/**********************************************************************************************/
	class HMIColorControl : public HMIControl
	{
	public:
		HMIColorControl(const SmartData& sd);
		HMIColorControl(const string& strName);

		HMIColorControl(const SmartData& sd, const std::string& serverKey);
		HMIColorControl(const string& strName, const std::string& serverKey);

		HMI_COLOR& ForeColor();
		const HMI_COLOR& ForeColor() const;

		HMI_COLOR& BackColor();
		const HMI_COLOR& BackColor() const;

		virtual SmartData& GetData();

		virtual void UpdateControl(const SmartData& sd);

	protected:
		HMI_COLOR _foreColor;
		HMI_COLOR _backColor;
	};

	inline HMI_COLOR& HMIColorControl::ForeColor()
	{
		return _foreColor;
	}

	inline const HMI_COLOR& HMIColorControl::ForeColor() const
	{
		return _foreColor;
	}

	inline HMI_COLOR& HMIColorControl::BackColor()
	{
		return _backColor;
	}

	inline const HMI_COLOR& HMIColorControl::BackColor() const
	{
		return _backColor;
	}


	/*********************************************************************************************/
	/*														HMIList																*/
	/**********************************************************************************************/
	class HMIList : public HMIColorControl
	{
	public:
		HMIList(const SmartData& sd);
		HMIList(const string& strName);

		HMIList(const SmartData& sd, const std::string& serverKey);
		HMIList(const string& strName, const std::string& serverKey);

		typedef std::vector<std::string> List;
	public:
		void AddListItem(const std::string& strItem);
		void AddListItem(const List& lst);
		void ClearList();
		HMIList::List& ListItems();
		std::string ListItems(int nPos) const;
		SmartData& GetData();

		SmartData& Text();
		
		int ListItemCount() const;

		void UpdateControl(const SmartData& sd);
	protected:
		void UpdateList(const SmartData& sd);
	private:
		List _lst;
	};

	/*********************************************************************************************/
	/*														HMIList																*/
	/**********************************************************************************************/
	class HMIDropdownList : public HMIList
	{
	public:
		HMIDropdownList(const SmartData& sd) : HMIList(sd) {}
		HMIDropdownList(const string& strName) : HMIList(strName){}

		HMIDropdownList(const SmartData& sd, const std::string& serverKey) : HMIList(sd, serverKey) {}
		HMIDropdownList(const string& strName, const std::string& serverKey) : HMIList(strName, serverKey){}
	};
   
	/*********************************************************************************************/
	/*													           	HMIGrid																         */
	/**********************************************************************************************/
	class HMIGrid : public HMIControl
	{
	public:
		class Row
		{
			friend class HMIGrid;
		public:
			SmartData& Column(int nPos);
			std::string ColumnName(int nPos);
			SmartData& Column(const std::string& strColumn);
			SmartData& operator[] (const std::string& strColumn);
			int ColumnCount() const;
			const SmartData& GetData() const
			{
				return _rsd;
			}
		private:
			Row(const SmartData& sd){  _rsd=sd; }
			
		private:
			SmartData _rsd;
		};

	public:
		HMIGrid(const SmartData& sd);
		HMIGrid(const string& strName);

		HMIGrid(const SmartData& sd, const std::string& serverKey);
		HMIGrid(const string& strName, const std::string& serverKey);

		typedef vector<Row> ROWS;

		/*
		新增row
		*/
		Row& AddRow();


		/**********************************************************************
		 *  概述: 删除指定行
		 *  函数名： DeleteRow 
		 *  返回值： void	 	
		 *  参数列表：	参数类型    					取值范围     		    描述
		 *    nRow  :    [IN/OUT] int	        行数 0-based
		 *
		 *  版本历史		
		 *       1.0    2010-11-08  Haykin-2010    //TODO请添加本次主要修改内容
		 *  
		 **********************************************************************/
		void DeleteRow(int nRow);

	
		/**********************************************************************
		 *  概述: 返回函数
		 *  函数名： RowCount 
		 *  返回值： int	 	//TODO:返回值描述
		 *  参数列表：	参数类型    					取值范围     		    描述
		 *
		 *  版本历史		
		 *       1.0    2010-11-08  Haykin-2010    //TODO请添加本次主要修改内容
		 *  
		 **********************************************************************/
		int RowCount();


		/**********************************************************************
		 *  概述: 返回行集
		 *  函数名： Rows 
		 *  返回值： ROWS&	 	行集
		 *  参数列表：	参数类型    					取值范围     		    描述
		 *
		 *  版本历史		
		 *       1.0    2010-11-08  Haykin-2010    //TODO请添加本次主要修改内容
		 *  
		 **********************************************************************/
		ROWS& Rows();
		const ROWS& Rows() const;


		/**********************************************************************
		 *  概述: 返回指定行
		 *  函数名： Rows 
		 *  返回值： Row&	 	
		 *  参数列表：	参数类型    					取值范围     		    描述
		 *    nRow  :    [IN/OUT] int	         行数 0_based
		 *
		 *  版本历史		
		 *       1.0    2010-11-08  Haykin-2010    //TODO请添加本次主要修改内容
		 *  
		 **********************************************************************/
		Row& Rows(int nRow);
		const Row& Rows(int nRow) const;

		void Clear();

		SmartData& GetData();

		void UpdateControl(const SmartData& sd);

	private:
		void UpdateRow(const SmartData& sd);
	private:
		ROWS _rows;
	};

	/*********************************************************************************************/
	/*													           	HMIChart 															         */
	/**********************************************************************************************/
	class HMIChart : public HMIControl
	{
	public:
		class HMILine
		{
			friend class HMIChart;
		public:
			int _index;
			int _thickness;
			std::string _label;
			int _legendEntry;
			std::string _toolTipText;
			std::string _toolTipTextLegend;
			HMI_COLOR _color;
			std::string _display;

			typedef struct _DataValue{
				double x;
				double y;
				_DataValue()
				{
					x = 0.0;
					y = 0.0;
				}

				_DataValue(double x, double y)
				{
					this->x = x;
					this->y = y;
				}
			}DataValue;

			typedef std::vector<DataValue> LineData;
			LineData _data;

			DataValue& Data(int n);

		public:

			/**********************************************************************
			 *  概述: 删除所有坐标数据数据
			 *  函数名： ClearData 
			 *  返回值： void	 	//TODO:返回值描述
			 *  参数列表：	参数类型    					取值范围     		    描述
			 *
			 *  版本历史		
			 *       1.0    2010-11-08  Haykin-2010    //TODO请添加本次主要修改内容
			 *  
			 **********************************************************************/
			void ClearData();


			/**********************************************************************
			 *  概述: 新增坐标值
			 *  函数名： AddData 
			 *  返回值： void	 	//TODO:返回值描述
			 *  参数列表：	参数类型    					取值范围     		    描述
			 *    x  :    [IN/OUT] double						x
			 *    y  :    [IN/OUT] double						y
			 *
			 *  版本历史		
			 *       1.0    2010-11-08  Haykin-2010    //TODO请添加本次主要修改内容
			 *  
			 **********************************************************************/
			void AddData(double x, double y);

			int DataSize();
		protected:
			HMILine(int nIndex): _index(nIndex), _thickness(1), _legendEntry(-1), _color(HMI_COLOR_DEFAULT)
			{
			}

			HMILine& operator=(const SmartData& sd);
		};
	public:
		HMIChart(const SmartData& sd);
		HMIChart(const string& strName);

		HMIChart(const SmartData& sd, const std::string& serverKey);
		HMIChart(const string& strName, const std::string& serverKey);

		~HMIChart();

	public:
		typedef std::vector<HMILine*> LINES;
		typedef std::vector<LINES> GROUPS;

		typedef enum {
			CHART_GROUP_X =0
		   ,CHART_GROUP_Y = 1 
		}EN_CHART_GROUP;

	public:

		/**********************************************************************
		 *  概述: 新增曲线
		 *  函数名： AddLine 
		 *  返回值： HMILine&	 	曲线
		 *  参数列表：	参数类型    					取值范围     		    描述
		 *    grp  :    [IN/OUT] int	         
		 *
		 *  版本历史		
		 *       1.0    2010-11-08  Haykin-2010    //TODO请添加本次主要修改内容
		 *  
		 **********************************************************************/
		HMILine& AddLine(EN_CHART_GROUP grp = CHART_GROUP_X);
		SmartData& GetData();
		//HMILine& Line(int index, EN_CHART_GROUP grp = CHART_GROUP_X);
		void UpdateControl(const SmartData& sd);
		void Clear();
		
	protected:
		void UpdateGroup(const SmartData& sd);

	protected:
		GROUPS _grp;
	};


	/*********************************************************************************************/
	/*													           	HMIText  															         */
	/**********************************************************************************************/
	template<typename T>
	class HMITextTrait;

	/*template<>
	class HMITextTrait<short>
	{
		static short NullValue() { return iPlature::I2_INV; }
	};*/

	template<>
	class HMITextTrait<int>
	{
	public:
		static int NullValue() { return iPlature::I_INV; }
	};

	template<>
	class HMITextTrait<float>
	{
	public:
		static float NullValue() { return iPlature::F_INV; }
	};

	template<>
	class HMITextTrait<double>
	{
	public:
		static double NullValue() { return iPlature::D_INV; }
	};

	template<>
	class HMITextTrait<std::string>
	{
	public:
		static std::string NullValue() { return ""; }
	};

	template<typename T>
	class HMIText : public HMIColorControl
	{
	public:
		HMIText(const SmartData& sd);
		HMIText(const string& strName);

		HMIText(const SmartData& sd, const std::string& serverKey);
		HMIText(const string& strName, const std::string& serverKey);

		T& Text();
		const T& Text() const;

		SmartData& GetData();
		virtual void UpdateControl(const SmartData& sd);

		void SetAsNull();
		bool IsNull();
	protected:
		T _txt;
	};

	template<typename T>
	HMIText<T>::HMIText(const SmartData& sd) : HMIColorControl(sd)
	{
		_txt = static_cast<T>(_sd["Text"]);
	}

	template<typename T>
	HMIText<T>::HMIText(const SmartData& sd, const std::string& serverKey) : HMIColorControl(sd, serverKey)
	{
		_txt = static_cast<T>(_sd["Text"]);
	}

	template<>
	HMIText<std::string>::HMIText(const SmartData& sd);

	template<>
	HMIText<std::string>::HMIText(const SmartData& sd, const std::string& serverKey);

	template<typename T>
	inline T& HMIText<T>::Text()
	{
		return _txt;
	}

	template<typename T>
	inline const T& HMIText<T>::Text() const
	{
		return _txt;
	}

	template<typename T>
	HMIText<T>::HMIText(const string& strName) : HMIColorControl(strName) {}

	template<typename T>
	HMIText<T>::HMIText(const string& strName, const std::string& serverKey) : HMIColorControl(strName, serverKey) {}

	template<typename T>
	SmartData& HMIText<T>::GetData()
	{
		_sd["Text"] = _txt;
		return HMIColorControl::GetData();
	}

	template<typename T>
	void HMIText<T>::UpdateControl(const SmartData& sd)
	{
		HMIColorControl::UpdateControl(sd);
		_txt = static_cast<T>(_sd["Text"]);
	}

	template<>
	void HMIText<std::string>::UpdateControl(const SmartData& sd);


	template<typename T>
	void HMIText<T>::SetAsNull()
	{
		_txt = HMITextTrait<T>::NullValue();
	}

	template<typename T>
	bool HMIText<T>::IsNull()
	{
		return _txt == HMITextTrait<T>::NullValue();
	}


	/*********************************************************************************************/
	/*													           	HMICheckBox  															         */
	/**********************************************************************************************/
	template<typename T=std::string>
	class HMICheckBox : public HMIText<T>
	{
	public:
		HMICheckBox(const SmartData& sd);
		HMICheckBox(const std::string& strName);

		HMICheckBox(const SmartData& sd, const std::string& serverKey);
		HMICheckBox(const std::string& strName, const std::string& serverKey);
	public:

		bool& Checked();
		bool Checked() const;

		void UpdateControl(const SmartData& sd);
		SmartData& GetData();
	private:
		void SetSmartData(const SmartData& sd);
	private:
		bool _check;
	};

	template<typename T>
	HMICheckBox<T>::HMICheckBox(const SmartData& sd) : HMIText<T>(sd)
	{
		SetSmartData(sd);
	}

	template<typename T>
	HMICheckBox<T>::HMICheckBox(const std::string& strName) : HMIText<T>(strName), _check(false) {}

	template<typename T>
	HMICheckBox<T>::HMICheckBox(const SmartData& sd, const std::string& serverKey) : HMIText<T>(sd, serverKey)
	{
		SetSmartData(sd);
	}

	template<typename T>
	HMICheckBox<T>::HMICheckBox(const std::string& strName, const std::string& serverKey)
		: HMIText<T>(strName, serverKey), _check(false) {}

	template<typename T>
	inline bool& HMICheckBox<T>::Checked()
	{
		return _check;
	}

	template<typename T>
	inline bool HMICheckBox<T>::Checked() const
	{
		return _check;
	}

	template<typename T>
	SmartData& HMICheckBox<T>::GetData()
	{
		this->_sd["Checked"] = static_cast<int>(_check);
		return HMIText<T>::GetData();
	}

	template<typename T>
	void HMICheckBox<T>::UpdateControl(const SmartData& sd)
	{
		SetSmartData(sd);
		HMIText<T>::UpdateControl(sd);
	}

	template<typename T>
	void HMICheckBox<T>::SetSmartData(const SmartData& sd)
	{
		int nCheck = sd["Checked"];
		if (nCheck > 0)
		{
			_check = true;
		}
		else
		{
			_check = false;
		}
	}


	template<typename T=std::string>
	class HMIRadioBox : public HMICheckBox<T>
	{
	public:
		HMIRadioBox(const SmartData& sd);
		HMIRadioBox(const std::string& strName);

		HMIRadioBox(const SmartData& sd, const std::string& serverKey);
		HMIRadioBox(const std::string& strName, const std::string& serverKey);
	};

	template<typename T>
	HMIRadioBox<T>::HMIRadioBox(const SmartData& sd) : HMICheckBox<T>(sd){}

	template<typename T>
	HMIRadioBox<T>::HMIRadioBox(const std::string& strName): HMICheckBox<T>(strName){}

	template<typename T>
	HMIRadioBox<T>::HMIRadioBox(const SmartData& sd, const std::string& serverKey): HMICheckBox<T>(sd, serverKey){}

	template<typename T>
	HMIRadioBox<T>::HMIRadioBox(const std::string& strName, const std::string& serverKey):HMICheckBox<T>(strName, serverKey){}
	/*********************************************************************************************/
	/*													           	HMIComBox  														       */
	/**********************************************************************************************/
	template<typename T = std::string>
	class HMIComBox : public HMIText<T>
	{
	public:
		typedef std::vector<T> List;
	public:
		HMIComBox(const SmartData& sd);
		HMIComBox(const std::string& strName);

		HMIComBox(const SmartData& sd, const std::string& serverKey);
		HMIComBox(const std::string& strName, const std::string& serverKey);

		List& ListItems();

		// get item value
		T ListItems(int nPos) const;

		//add one item
		void AddListItem(const T& item);

		//remove all items
		void ClearListItem();

		//get items count
		int ListItemSize();

		SmartData& GetData();

		void UpdateControl(const SmartData& sd);
	private:
		void SetSmartData(const SmartData& sd);
	private:
		List _lst;
	};

	template<typename T>
	void HMIComBox<T>::SetSmartData(const SmartData& sd)
	{
		_lst.clear();
		for (int i=0; i < sd["List"].size(); i++)
		{
			T item = static_cast<T>(sd["List"][i]["Item"]);
			_lst.push_back(item);
		}
	}

	template< >
	void HMIComBox<std::string>::SetSmartData(const SmartData& sd);

	template<typename T>
	HMIComBox<T>::HMIComBox(const SmartData& sd) : HMIText<T>(sd)
	{
		SetSmartData(sd);
	}

	template<typename T>
	HMIComBox<T>::HMIComBox(const std::string& strName) : HMIText<T>(strName)
	{
		
	}

	template<typename T>
	HMIComBox<T>::HMIComBox(const SmartData& sd, const std::string& serverKey) : HMIText<T>(sd, serverKey)
	{
		SetSmartData(sd);
	}

	template<typename T>
	HMIComBox<T>::HMIComBox(const std::string& strName, const std::string& serverKey) : HMIText<T>(strName, serverKey)
	{
	}

	template<typename T>
	void HMIComBox<T>::UpdateControl(const SmartData& sd)
	{
		HMIText<T>::UpdateControl(sd);
		SetSmartData(sd);
	}

	template<typename T>
	typename HMIComBox<T>::List& HMIComBox<T>::ListItems()
	{
		return _lst;
	}

	template<typename T>
	T HMIComBox<T>::ListItems(int nPos) const
	{
		return _lst[nPos];
	}

	template<typename T>
	void HMIComBox<T>::AddListItem(const T& item)
	{
		_lst.push_back(item);
	}

	template<typename T>
	SmartData& HMIComBox<T>::GetData()
	{
		//(this->_sd)["Text"] = _txt;
		int nCount = static_cast<int>(_lst.size());
		if (nCount == 0)
		{
			this->_sd["List"].clear();
		}
		else
		{
			(this->_sd)["List"]((this->_sdTyp)["List"], nCount);
			for (int i=0; i<nCount; i++)
			{
				this->_sd["List"][i]["Item"] = _lst[i];
			}
		}
		return HMIText<T>::GetData();
	}

	//remove all items
	template<typename T>
	void HMIComBox<T>::ClearListItem() { _lst.clear(); }

	//get items count
	template<typename T>
	int HMIComBox<T>::ListItemSize() { return (int)_lst.size(); }

	/*********************************************************************************************/
	/*													           	HMILabel  															         */
	/* value=Name=S64,Text=S100,BackColor=I4,ForeColor=I4													*/
	/**********************************************************************************************/
	template<typename T = std::string>
	class HMILabel : public HMIText<T>
	{
	public:
		HMILabel(const SmartData& sd) : HMIText<T>(sd) {}
		HMILabel(const std::string& strName) : HMIText<T>(strName) {}

		HMILabel(const SmartData& sd, const std::string& serverKey) : HMIText<T>(sd, serverKey) {}
		HMILabel(const std::string& strName, const std::string& serverKey) : HMIText<T>(strName, serverKey) {}
	};

	/*********************************************************************************************/
	/*													           	HMIImageBox														         */
	/**********************************************************************************************/
	class HMIImageBox : public HMIControl
	{
	public:
		HMIImageBox(const SmartData& sd);
		HMIImageBox(const std::string& strName);

		HMIImageBox(const SmartData& sd, const std::string& serverKey);
		HMIImageBox(const std::string& strName, const std::string& serverKey);

		bool& Visible();
		bool Visible() const;

		void UpdateControl(const SmartData& sd);
		SmartData& GetData();
	private:
		void SetSmartData();
	private:
		bool _bVisible;
	};

	inline bool& HMIImageBox::Visible()
	{
		return _bVisible;
	}
	inline bool HMIImageBox::Visible() const
	{
		return _bVisible;
	}
   
}

