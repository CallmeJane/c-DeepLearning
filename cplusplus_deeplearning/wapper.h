#pragma once
/*
	实现流的加密
	流的种类（3种）：文件流，网络流，控制台流（cmd或者键盘输入）
	加密的方式（4种）：不加密，MD5，对称加密，非对称加密

	利用继承的方式需要需要实现：3*4个类
	利用包装器只需要：3+4个类

	包装（wapper）/装饰（detetor）的主要思想：
	（组合）替代（继承）
	方法类（各种流）和包装类（对各种流进行加密）都继承自同一接口(都有同一种方法)，
	不同包装类对（什么流，所有流继承同一虚基类）进行（什么包装）是动态绑定的。
	
	方法基类：虚基类，所有类统一接口
	包装基类：虚基类，统一接口，统一数据
	包装类和方法类都要继承统一虚基类：因为包装类的构造函数也可以包装类，表明包装的
	先后循序
	https://blog.csdn.net/noteless/article/details/82599345（关于手抓饼的包装模式，通俗易懂）
*/
#include<iostream>
#include<string>

using std::cout;
using std::endl;
using std::string;

class StreamBase
{
public:
	virtual string io() = 0;        //虚基类,纯虚函数
};


//方法类：文件流、网络流、控制台流
class FileStream:public StreamBase {
public:
	string io()				//这里应该也可以不用虚函数？
	{
		return "FileStream";
	}
};

class NetworkStream :public StreamBase {
public:
	string io()
	{
		return "NetworkStream";
	}
};

class ControlStream :public StreamBase {
public:
	virtual string io()
	{
		return "ControlStream";
	}
};

//包装类：不加密，MD5加密，对称加密，非对称加密
class Detector :public StreamBase {
public:
	Detector(StreamBase *ptr):p_stream(ptr){}
	//io 仍然是纯虚函数(是不对的，因为Detector需要调用Stream的方法)
	string io()
	{
		return p_stream->io();
	}
private:
	StreamBase *p_stream;
};

class NormDetector :public Detector {
public:
	NormDetector(StreamBase *ptr):Detector(ptr){}
	string io()
	{
		string ret=Detector::io()+"+"+norm();
		return ret;
	}

private:
	string norm()
	{
		return "普通加密";
	}
};

class MD5Detector :public Detector {
public:
	MD5Detector(StreamBase *ptr):Detector(ptr){}
	string io()
	{
		return Detector::io() + "+" + MD5();
	}
private:
	string MD5()
	{
		return "MD5";
	}
};

class SymmetricDetector:public Detector {
public:
	SymmetricDetector(StreamBase *ptr) :Detector(ptr){}
	string io()
	{
		return Detector::io() +"+"+ symmetric();
	}
private:
	string symmetric()
	{
		return "symmetric";
	}
};

class AsymmetricDetector :public Detector{
public:
	AsymmetricDetector(StreamBase *ptr) :Detector(ptr){}
	string io()
	{
		return Detector::io() + "+" + asymmetric();
	}
private:
	string asymmetric()
	{
		return "asymmetric";
	}
};

int main()
{
	StreamBase* filestream = new FileStream();
	cout<< filestream->io()<<endl;
	cout << sizeof(StreamBase) << endl;            //4=vfptr
	//cout << offsetof(FileStream, __vfptr) << endl;

	Detector* detector_norm = new NormDetector(filestream);
	cout << detector_norm->io() << endl;
	cout << sizeof(Detector) << endl;			  //8=Detector+p_stream
	cout << sizeof(NormDetector) << endl;		  //8
	//cout << offsetof(Detector, p_stream) << endl;

	Detector* detector_md5 = new MD5Detector(detector_norm);
	cout << detector_md5->io()<<endl;

	Detector* detector_symmertric = new SymmetricDetector(detector_norm);
	cout << detector_symmertric->io() << endl;

	system("pause");
}

