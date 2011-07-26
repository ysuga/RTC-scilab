/**
 * Package  : RTC-scilab.
 *   RTC-scilab is the inter-connecting library between scilab and OpenRTM.
 *
 * File     : RTCSciInPort.h
 * Date     : 2010/02/28
 * author   : Yuki Suga (E-mail: ysuga@ysuga.net)
 * copyright: ysuga.net 2010, all rights reserved.
 * URL      : http://www.ysuga.net/rtm/rtc_scilab/index.html
 *
 * This file must be used under the terms of GNU Public License version 3.
 * This source file is licensed as described in the file license.txt, which
 * you should have received as part of this distribution.
 */

#ifndef RTCSCIINPORT_HEADER_INCLUDED
#define RTCSCIINPORT_HEADER_INCLUDED


class RTCSciInPortBase
{
protected:
	std::string m_TypeCode;
	RTC::InPortBase* m_pPort;

	ScilabComp* m_pOwner;
	int m_OwnerHandle;
	std::string m_Name;

	int m_SelfHandle;
public:

	void SetScilabComp(ScilabComp* pOwner){m_pOwner= pOwner;}
	void SetOwnerHandle(int handle) {m_OwnerHandle = handle;}
	void SetSelfHandle(int handle) {m_SelfHandle = handle;}

	RTC::InPortBase& GetPort() { return *m_pPort; }

	operator RTC::InPortBase&(){return *m_pPort;}
	ScilabComp* GetOwner() {return m_pOwner;}
	int GetOwnerHandle() {return m_OwnerHandle;}
	int GetSelfHandle() {return m_SelfHandle;}

	std::string& GetName() {return m_Name;}
	std::string& GetTypeCode() {return m_TypeCode;}
public:
	RTCSciInPortBase(const char* name){m_Name = name;}
	virtual ~RTCSciInPortBase(){}

public:
	virtual int Poll(void) = 0;

	virtual int Read(void) = 0;

	virtual int Get(void* dst, unsigned int size) = 0;
};


template<class DataType, typename VType>
class RTCSciInPort : public RTCSciInPortBase
{
private:
	DataType m_Value;
	
public:

public:
	RTCSciInPort(const char* name) : RTCSciInPortBase(name)
	{
		m_TypeCode = toTypename<DataType>();
		m_pPort  = new InPort<DataType>(name, m_Value);
	}

	~RTCSciInPort()
	{
		delete m_pPort;
	}

public:

	int Poll(void) {
		//if ((*m_pOwner->get_owned_contexts())[0]->get_component_state(RTC::RTObject::_duplicate(m_pOwner->getObjRef())) != RTC::ACTIVE_STATE) {
		if(!m_pOwner->isActive()) {
			return 0;
		}
		return ((InPort<DataType>*)m_pPort)->isNew();
	}

	int Read(void) {
		((InPort<DataType>*)m_pPort)->read();
		//		((InPort<DataType>*)m_pPort)->get()
		return 1;
	}

	int Get(void* dst, unsigned int size) {
		VType* pbuf = (VType*)dst;
		return Get(pbuf, size);
	}

	int Get(VType* dst, unsigned int size) {
		if(size != 1) return -1;
		*dst = m_Value.data;
		return 0;
	}

};

template<class DataType, class VType>
class RTCSciSeqInPort : public RTCSciInPortBase
{
private:
	std::string TypeCode;
	DataType* m_pValue;
public:

public:
	RTCSciSeqInPort(const char* name) : RTCSciInPortBase(name)
	{
		TypeCode = toTypename<DataType>();
		m_pValue = new DataType();
		m_pPort  = new InPort<DataType>(name, *m_pValue);
	}

	~RTCSciSeqInPort()
	{
		delete m_pValue;
		delete m_pPort;
	}

public:

	int Poll(void) {
		
		//if ((*m_pOwner->get_owned_contexts())[0]->get_component_state(RTC::RTObject::_duplicate(m_pOwner->getObjRef())) != RTC::ACTIVE_STATE) {
		if(!m_pOwner->isActive()) {
			return 0;
		}

		return ((InPort<DataType>*)m_pPort)->isNew();
	}

	int Read(void) {
		((InPort<DataType>*)m_pPort)->read();
		return m_pValue->data.length();
	}

	int Get(void* dst, unsigned int size) {
		VType* pbuf = (VType*)dst;
		return Get(pbuf, size);
	}

	int Get(VType* dst, unsigned int size) {
		memcpy(dst, &(m_pValue->data[0]), size*sizeof(VType));
		return 0;
		//*dst = *m_pValue;
	}
};

#endif

