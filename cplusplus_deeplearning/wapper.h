#pragma once
/*
	ʵ�����ļ���
	�������ࣨ3�֣����ļ�����������������̨����cmd���߼������룩
	���ܵķ�ʽ��4�֣��������ܣ�MD5���ԳƼ��ܣ��ǶԳƼ���

	���ü̳еķ�ʽ��Ҫ��Ҫʵ�֣�3*4����
	���ð�װ��ֻ��Ҫ��3+4����

	��װ��wapper��/װ�Σ�detetor������Ҫ˼�룺
	����ϣ�������̳У�
	�����ࣨ���������Ͱ�װ�ࣨ�Ը��������м��ܣ����̳���ͬһ�ӿ�(����ͬһ�ַ���)��
	��ͬ��װ��ԣ�ʲô�����������̳�ͬһ����ࣩ���У�ʲô��װ���Ƕ�̬�󶨵ġ�
	
	�������ࣺ����࣬������ͳһ�ӿ�
	��װ���ࣺ����࣬ͳһ�ӿڣ�ͳһ����
	��װ��ͷ����඼Ҫ�̳�ͳһ����ࣺ��Ϊ��װ��Ĺ��캯��Ҳ���԰�װ�࣬������װ��
	�Ⱥ�ѭ��
	https://blog.csdn.net/noteless/article/details/82599345��������ץ���İ�װģʽ��ͨ���׶���
*/
#include<iostream>
#include<string>

using std::cout;
using std::endl;
using std::string;

class StreamBase
{
public:
	virtual string io() = 0;        //�����,���麯��
};


//�����ࣺ�ļ�����������������̨��
class FileStream:public StreamBase {
public:
	string io()				//����Ӧ��Ҳ���Բ����麯����
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

//��װ�ࣺ�����ܣ�MD5���ܣ��ԳƼ��ܣ��ǶԳƼ���
class Detector :public StreamBase {
public:
	Detector(StreamBase *ptr):p_stream(ptr){}
	//io ��Ȼ�Ǵ��麯��(�ǲ��Եģ���ΪDetector��Ҫ����Stream�ķ���)
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
		return "��ͨ����";
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

