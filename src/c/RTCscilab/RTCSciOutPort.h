/**
 * Package  : RTC-scilab.
 *   RTC-scilab is the inter-connecting library between scilab and OpenRTM.
 *
 * File     : RTCSciOutPort.h
 * Date     : 2010/02/28
 * author   : Yuki Suga (E-mail: ysuga@ysuga.net)
 * copyright: ysuga.net 2010, all rights reserved.
 * URL      : http://www.ysuga.net/rtm/rtc_scilab/index.html
 *
 * This file must be used under the terms of GNU Public License version 3.
 * This source file is licensed as described in the file license.txt, which
 * you should have received as part of this distribution.
 */
#ifndef RTCSCIOUTPORT_HEADER_INCLUDED
#define RTCSCIOUTPORT_HEADER_INCLUDED


class RTCSciOutPortBase
{
protected:
	std::string TypeCode;

	RTC::OutPortBase* m_pPort;

	ScilabComp* m_pOwner;
	int m_OwnerHandle;
	std::string m_Name;

	int m_SelfHandle;
public:
	void SetScilabComp(ScilabComp *pOwner) { m_pOwner = pOwner; }
	void SetOwnerHandle(int handle) {m_OwnerHandle = handle;}
	void SetSelfHandle(int handle) {m_SelfHandle = handle;}

	RTC::OutPortBase& GetPort() { return *m_pPort; }

	operator RTC::OutPortBase&(){return *m_pPort;}
	ScilabComp* GetOwner() {return m_pOwner;}
	int GetOwnerHandle() {return m_OwnerHandle;}
	int GetSelfHandle() {return m_SelfHandle;}

	std::string& GetName(){return m_Name;}
	std::string& GetTypeCode() {return TypeCode;}
public:
	RTCSciOutPortBase(const char* name){m_Name = name;}
	virtual ~RTCSciOutPortBase(){}

public:
	virtual int Write(void* data, unsigned int size) = 0;

};


template<class DataType, typename VType>
class RTCSciOutPort : public RTCSciOutPortBase
{
private:
//	std::string TypeCode;
	DataType* m_pValue;
	
public:

public:
	RTCSciOutPort(const char* name) : RTCSciOutPortBase(name)
	{
		TypeCode = toTypename<DataType>();
		//		m_pValue = new typename DataType();
		m_pValue = new DataType();
		m_pPort  = new OutPort<DataType>(name, *m_pValue);
	}

	~RTCSciOutPort()
	{
		delete m_pValue;
		delete m_pPort;
	}

public:

	int Write(void* data, unsigned int size) {
		VType *buf = (VType*)data;
		return Write(buf, size);
	}

	int Write(VType* data, unsigned int size)
	{
		//if ((*m_pOwner->get_owned_contexts())[0]->get_component_state(RTC::RTObject::_duplicate(m_pOwner->getObjRef())) != RTC::ACTIVE_STATE) {
		if(!m_pOwner->isActive()) {
			return 0;
		}
		if(size != 1) return -1;
		m_pValue->data = *data;
		return ((OutPort<DataType>*)m_pPort)->write();
	}

};

template<class DataType, class VType>
class RTCSciSeqOutPort : public RTCSciOutPortBase
{
private:
	DataType* m_pValue;
	
public:

public:
	RTCSciSeqOutPort(const char* name) : RTCSciOutPortBase(name)
	{
		TypeCode = toTypename<DataType>();
		//m_pValue = new typename DataType();
		m_pValue = new DataType();
		m_pPort  = new OutPort<DataType>(name, *m_pValue);
	}

	~RTCSciSeqOutPort()
	{
		delete m_pValue;
		delete m_pPort;
	}

public:
	int Write(void* data, unsigned int size) {
		VType* buf = (VType*)data;
		return Write(buf, size);	
	}

	int Write(VType* value, unsigned int size)
	{
		//if ((*m_pOwner->get_owned_contexts())[0]->get_component_state(RTC::RTObject::_duplicate(m_pOwner->getObjRef())) != RTC::ACTIVE_STATE) {
		if(!m_pOwner->isActive()) {
			return 0;
		}
		m_pValue->data.length(size);
		//m_pValue->data.operator[](1);
		memcpy(&(m_pValue->data[0]), value, size*sizeof(VType));
		return ((OutPort<DataType>*)m_pPort)->write();
	}
};



#endif



