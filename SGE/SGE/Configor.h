/*
	A little config thingy for C++
	Created by C0BRA
	Copyright XiaTek.org 2012
	Released under the MIT licence
*/

#ifndef CONFIGOR_H
#define CONFIGOR_H

#include <string>
#include <list>

class IConfigorNode;
class CConfigor;
typedef std::list<IConfigorNode*> IConfigorNodeList;

extern CConfigor* g_pConfigor;

class IConfigorNode
{
public:
	virtual ~IConfigorNode() {};
	virtual std::string GetName() = 0;
	virtual unsigned long GetDataLength() = 0;
	virtual unsigned char* GetData() = 0;
	virtual void SetData(unsigned char* pData, unsigned long Length) = 0;
	virtual char* GetString() = 0;
	virtual void SetString(const char* pString) = 0;
	virtual IConfigorNode* GetChild(std::string Name) = 0;
	virtual IConfigorNode* GetParent() = 0;
	virtual void AddChild(IConfigorNode* Node) = 0;
	virtual void RemoveChild(IConfigorNode* Node) = 0;
	virtual IConfigorNodeList* GetChildren() = 0;
	virtual IConfigorNode& operator[](const std::string& key) = 0;
	virtual void operator=(char* pData) = 0;

	// Ease of use functions
	template<typename T> T GetValue(T Default);
	template<typename T> void SetValue(T Default);
};

typedef std::list<IConfigorNode*> IConfigorNodeList;

class CConfigorNode : public IConfigorNode
{
protected:
	IConfigorNodeList m_Children;
	IConfigorNode* m_pParent;

	unsigned long m_Length;
	unsigned char* m_pData;

	void DestroyData();

	std::string m_Name;

public:
	CConfigorNode(IConfigorNode* pParent, std::string Name);
	~CConfigorNode();

	std::string GetName();
	unsigned long GetDataLength();
	unsigned char* GetData();
	void SetData(unsigned char* pData, unsigned long Length);
	char* GetString();
	void SetString(const char* pString);
	IConfigorNode* GetChild(std::string Name);
	IConfigorNode* GetParent();
	void AddChild(IConfigorNode* Node);
	void RemoveChild(IConfigorNode* Node);
	IConfigorNodeList* GetChildren();
	IConfigorNode& operator[](const std::string& key);
	void operator=(char* pData);
};

namespace ConfigorLexType
{
	const extern int None;
	const extern int Token;
	const extern int String;
	const extern int NewLine; // for line counting only
}

struct CConfigorLexNode
{
	int Type;
	void* Value;
	unsigned long Length;
	std::string Error;
};

typedef std::list<CConfigorLexNode*> CConfigorLexNodeList;

class CConfigor
{
	IConfigorNode* m_pRootNode;
	unsigned long m_CurrentParseLine;
	unsigned char* m_pCurrentParseChar;

	std::string m_Error;

	// will be copied
	CConfigorLexNodeList Lexify(char* Input, unsigned long Length);
	std::string ParseQuotes(char** Out, unsigned long* Length, char* End);
public:
	CConfigor();
	~CConfigor();
	bool LoadFromFile(const std::string& Name);
	bool LoadFromString(char* Input, unsigned long Length);
	bool SaveToFile(const std::string& Name);
	IConfigorNode* GetRootNode();
	std::string GetError();
	IConfigorNode& operator[](const std::string& Index);
};

template<typename T> T IConfigorNode::GetValue(const T Default) // Sets the nodes value to the default if it doesn't exist too
{
	if(!GetData())
	{
		SetValue<T>(Default);
		return Default;
	}
	
	try
	{
		T ret;
		std::stringstream ss;
		ss << GetString();
		ss >> ret;

		return ret;
	}
	catch(...)
	{
		SetValue<T>(Default);
		return Default;
	}
}

template<typename T> void IConfigorNode::SetValue(const T Value)
{
	SetData(0, 0); // This should simulate destroying data

	std::string val;
	std::stringstream ss;
	
	ss << Value;
	ss >> val;

	SetString(val.c_str());
}

#endif