#pragma once 
#ifndef   _CraneEvadeRequestBase_ 
#define   _CraneEvadeRequestBase_ 

#include "DataAccess.h"
#include "log4cplus/LOG.h"

namespace Monitor
{




	class  CraneEvadeRequestBase
	{






	public:
		CraneEvadeRequestBase( void );
		~CraneEvadeRequestBase( void );
		void  logOutValues();

	private:
		void initValues();
		//1.TARGET_CRANE_NO
	private:
		string  targetCraneNO ;
	public:
		string  getTargetCraneNO( ) ;
		void    setTargetCraneNO( string theVal ) ;


		//2.SENDER
	private:
		string  sender ;

	public:
		string  getSender( ) ;
		void    setSender( string theVal ) ;


		//3.ORIGINAL_SENDER
	private:
		string  originalSender ;

	public:
		string  getOriginalSender( ) ;
		void    setOriginalSender( string theVal ) ;


		//4.EVADE_X_REQUEST
	private:
		long  evadeXRequest ;

	public:
		long    getEvadeXRequest( ) ;
		void    setEvadeXRequest( long theVal ) ;


		//5.EVADE_X
	private:
		long  evadeX ;

	public:
		long    getEvadeX( ) ;
		void    setEvadeX( long theVal ) ;


		//6.EVADE_DIRECTION
	private:
		string  evadeDirection ;

	public:
		string  getEvadeDirection( ) ;
		void    setEvadeDirection( string theVal ) ;


		//7.EVADE_ACTION_TYPE
	private:
		string  evadeActionType ;

	public:
		string   getEvadeActionType( ) ;
		void    setEvadeActionType( string theVal ) ;


		//8.STATUS
	private:
		string  status ;

	public:
		string   getStatus( ) ;
		void    setStatus( string theVal ) ;

		//9.PRIORITY
	private:
		double priority;
	public:
		double getPriority();
		void setPriority(double theValue);

	public:
		static const long ORDER_NO_EVADE;
		static const long ORDER_NO_BOARDING;
		static const long ORDER_NO_MANU_AUTO_SWITCH;
		static const long ORDER_NO_MANU_AUTO_SWITCH_TEST;

		//执行避让状态：EMPTY- 不需要执行 ， TO_DO - 等待执行避让 ， EXCUTING - 执行中，FINISHED - 执行完成

		const  static  string 	STATUS_EMPTY;
		const  static  string    STATUS_INIT;
		const  static  string 	STATUS_TO_DO;
		const  static  string 	STATUS_EXCUTING;
		const  static  string 	STATUS_FINISHED;

		const static   string    TYPE_RIGHT_NOW;
		const static   string    TYPE_AFTER_JOB;


	};



}
#endif