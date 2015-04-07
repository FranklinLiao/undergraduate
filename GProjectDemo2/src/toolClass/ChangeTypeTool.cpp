#include "stdafx.h"
#include "ChangeTypeTool.h"

	//string to int
	int ChangeTypeTool::stringToInt(string str) {
		int info;
		if(str!="") {
			info = atoi(str.c_str());
		} else{
			info=0;
		}
		return info;
	}
	
	long ChangeTypeTool::stringToLong(string str) {
		long info;
		if(str!="") {
			info = atol(str.c_str());
		} else{
			info=0;
		}
		return info;
	}
	 //string to double 
	 double ChangeTypeTool::stringToDouble(string str) {
		double info;
		if(str!="") {
			info =  atof(str.c_str());
		} else{
			info=0.0;
		}
		return info;
	 }

	 //string to double by ','
	 double ChangeTypeTool::stringSplitToDouble(string str) {
		 double info;
		 if(str!="") {
			 if(str.find(',')!=string::npos) {
				info = atof(str.substr(0,str.find(',')).c_str());
			 } else {
				info =  atof(str.c_str());
			 }
		 } else {
			info =0.0;
		 }
		 return info;
	 }
	 //string to char 
	 char* ChangeTypeTool::stringToChar(string str) {
		char* p;
		if(str!="") {
			 p = const_cast<char*>(str.c_str());
		} else{
			p=NULL;
		}
		return p;
	 }

	const char* ChangeTypeTool::stringToConstChar(string str) {
		const char *p;
		if(str!="") {
			p = str.c_str();
		}else {
			p=NULL;
		}
		 return p;
	 }

	//int to string
	string ChangeTypeTool::intToString(int i) {
		string info;
		stringstream ss;
		//int n = 123;
		ss<<i;
		info=ss.str();
		ss.clear();
		return info;
	}

	//double to string
	string ChangeTypeTool::doubleToString(double d) {
		string info;
		stringstream ss;
		ss<<d;
		info=ss.str();
		ss.clear();
		return info;
	}

	//long to string 
	string ChangeTypeTool::longToString(long d) {
		string info;
		stringstream ss;
		ss<<d;
		info=ss.str();
		ss.clear();
		return info;
	}
	//CString to String
	string ChangeTypeTool::cstringToString(CString cstringValue) {
		string str = cstringValue.GetBuffer(0);
		return str;
	}

/**
* @brief   按照自己的数据库的精度将经纬度进行转换
* @fullName	ChangeTypeTool::doubleToStringLonLat
* @param	d
* @param	precision
* @return	std::string
* @author	Franklin
* @date		2014/05/23
* @warning	
*/
string ChangeTypeTool::doubleToStringPrecise(double d,int precision/* =6 */) {
	ostringstream out;
	//int prec = std::numeric_limits::digits10;//18
	int prec = 18;
	out.precision(prec);//覆盖默认精度
	out<<d;
	string str= out.str(); //从流中取出字符串
	//规格化
	size_t n=str.find('.');
	int k = str.size();
	/*
	if ((n!=string::npos) //有小数点吗？
			&& (str.size()> n+precision)) //后面至少还有decplaces位吗？
		{
			str[n+precision+1]='\0';//覆盖第一个多余的数
		}
		*/
	if((n!=string::npos)&& (str.size()>n+precision)) {
		//此处未考虑到四舍五入的原则  直接截尾
		str = str.substr(0,n+precision);
	}
	str.swap(string(str.c_str()));//删除nul之后的多余字符
	return str;
}


	 //const char to string
	 string ChangeTypeTool::constCharToString(const char *c) {
		string str(c);
		return str;
	 }

	 /*
	 //string to int vector  只用到分号“；”
	 vector<int> ChangeTypeTool::stringToIntVector(string str,string sep) {
		vector<int> intVector;
		//string d = ";";
		//本处再用：
		vector<string> stringVector = ChangeTypeTool::stringToStringVector(str,sep);
		vector<string>::iterator iter=stringVector.begin( ); 
		for(;iter!=stringVector.end();)
		{
			intVector.push_back(ChangeTypeTool::stringToInt(*iter));
			iter++;
		}
		return intVector;
	 }

	 //string to string vector
	vector<string> ChangeTypeTool::stringToStringVector(string str,string sep) {
		//string sep = ":";
		vector<string> stringVector;
		stringVector = ChangeTypeTool::strSplit(str,sep);
		return stringVector;
	}
	*/

	/*
		//strtok 第一次调用传string  之后传递null
		char *p=strtok(ChangeTypeTool::stringToChar(str),d);   //开始进行分割  以d为分隔符  
		while(p) {
			stringVector.push_back(p);
			p=strtok(NULL,d);
		}
		return stringVector;
	 }
	 */

	 /*
	//将一个stringMap 变成一个map
	//只用到冒号“:”
	map<int,double> ChangeTypeTool::stringToIntMap(string str,string sep) {
		map<int,double> objectMap;
	    //string sep1 = ";";
		vector<string> stringMap=ChangeTypeTool::strSplit(str,sep);
		vector<string>::iterator iter = stringMap.begin();
		//int id =0;
		//double idValue=0;
		for(;iter!=stringMap.end();) {
			int id = ChangeTypeTool::stringToInt(*iter++);
			double idValue = ChangeTypeTool::stringToDouble(*iter);
			objectMap.insert(pair<int,double>(id,idValue));
		}
		return objectMap;
	}

	//只用到“；”
	map<string,double> ChangeTypeTool::stringToStringMap(string str,string sep) {
		map<string,double> objectMap;
		// string sep1 = ";";
		vector<string> stringMap=ChangeTypeTool::strSplit(str,sep);
		vector<string>::iterator iter = stringMap.begin();
		string idFreq = *iter++;
		double idValue = ChangeTypeTool::stringToDouble(*iter);
		objectMap.insert(pair<string,double>(idFreq,idValue));
		return objectMap;
	}


	vector<map<int,double>> ChangeTypeTool::stringToIntMapVector(string str,string sepOut,string sepIn) {
		vector<map<int,double>> finalData;
		vector<string> stringVector = ChangeTypeTool::stringToStringVector(str,sepOut);
		vector<string>::iterator iter = stringVector.begin();
		for(;iter!=stringVector.end();iter++) {
			map<int,double> mapData = ChangeTypeTool::stringToIntMap(*iter,sepIn);
			finalData.push_back(mapData);
		}
		return finalData;
	}

	vector<map<string,double>> ChangeTypeTool::stringToStringMapVector(string str,string sepOut,string sepIn) {
		vector<map<string,double>> finalData;
		vector<string> stringVector = ChangeTypeTool::stringToStringVector(str,sepOut);
		vector<string>::iterator iter = stringVector.begin();
		for(;iter!=stringVector.end();iter++) {
			map<string,double> mapData = ChangeTypeTool::stringToStringMap(*iter,sepIn);
			finalData.push_back(mapData);
		}
		return finalData;
	}

	//用冒号":"分割
	map<double,double> ChangeTypeTool::stringToDoubleMap(string str,string sep) {
		map<double,double> objectMap;
		// string sep1 = ";";
		vector<string> stringMap=ChangeTypeTool::strSplit(str,sep);
		vector<string>::iterator iter = stringMap.begin();
		double id =  ChangeTypeTool::stringToInt(*iter++);
		double idValue = ChangeTypeTool::stringToDouble(*iter);
		objectMap.insert(pair<double,double>(id,idValue));
		return objectMap;
	}
	*/
	/*
	//专门用于场强
	map<double,double> ChangeTypeTool::stringToDoubleMap(string str,string sep) {
		map<double,double> objectMap;
		// string sep1 = ";";
		vector<string> stringMap=ChangeTypeTool::strSplit(str,sep);
		vector<string>::iterator iter = stringMap.begin();
		double id =  ChangeTypeTool::stringToInt(*iter++);
		double idValue = ChangeTypeTool::stringToDouble(*iter);
		objectMap.insert(pair<double,double>(id,idValue));
		return objectMap;
	}
	*/
	/*
	//外面用；内部用:
	vector<map<double,double>> ChangeTypeTool::stringToDoubleMapVector(string str,string sepOut,string sepIn) {
		vector<map<double,double>> finalData;
		vector<string> stringVector = ChangeTypeTool::stringToStringVector(str,sepOut);
		vector<string>::iterator iter = stringVector.begin();
		for(;iter!=stringVector.end();iter++) {
			map<double,double> mapData = ChangeTypeTool::stringToDoubleMap(*iter,sepIn);
			finalData.push_back(mapData);
		}
		return finalData;
	}
	*/

	/*
	 //将一个stringMap 变成一个map
	map<int,double> ChangeTypeTool::stringToMap(string str,string sep) {
		 map<int,double> objectMap;
		// string sep1 = ";";
		 vector<string> stringMap=ChangeTypeTool::strSplit(str,sep);
		 vector<string>::iterator iter = stringMap.begin();
		 int id = ChangeTypeTool::stringToInt(*iter++);
		 double idValue = ChangeTypeTool::stringToDouble(*iter);
		 objectMap.insert(pair<int,double>(id,idValue));
		
		 return objectMap;
	 }

	vector<map<int,double>> ChangeTypeTool::stringToVectorMap(string str,string sep) {
		vector<map<int,double>> finalData;
		vector<string> stringVector = ChangeTypeTool::stringToStringVector(str);
		vector<string>::iterator iter = stringVector.begin();
		for(;iter!=stringVector.end();iter++) {
			map<int,double> mapData = ChangeTypeTool::stringToMap(*iter,sep);
			finalData.push_back(mapData);
		}
		return finalData;
	}

	*/

	
vector<int> ChangeTypeTool::strSplitPlus (string text){
	vector<int> valuesVector;
	int last_pos=0;
	string sep = "+";
	bool flag = false;
	int pos=0;
	vector<int> vectorWords;
	vector<int> plusValue1;
	vector<int> plusValue2;
	if(text!=""&&text!=" "&&text!="+") {
		while(true){
			pos=text.find_first_of(sep,last_pos);
			if(pos==string::npos){
				if(flag == false) { //没有+号的数据
					if(!text.substr(last_pos).empty()) {
						/*int value = ChangeTypeTool::stringToInt(text.substr(last_pos,pos-last_pos));
						vectorWords.push_back(value);*/
						vector<int> valuesVector = strSplitComma(text.substr(last_pos));
						return valuesVector;
					} else {
						valuesVector.push_back(0);
						return valuesVector;
					}
				} else {
					//得到+后面的那一部分
					if(!text.substr(last_pos).empty()) {
						plusValue2 = strSplitComma(text.substr(last_pos));
						for(int i = 0;i<plusValue1.size();i++) {
							int valueAll = plusValue1.at(i)+plusValue2.at(i);
							vectorWords.push_back(valueAll);
						}
						return vectorWords;
					} else {
						//针对特殊数据
						//plusValue2 = strSplitComma(text.substr(last_pos));
						for(int i = 0;i<plusValue1.size();i++) {
							int valueAll = plusValue1.at(i)+0;
							vectorWords.push_back(valueAll);
						}
						return vectorWords;
					}
				}
			}else{
				//得到+前面的那一部分
				flag = true;
				if(pos-last_pos!=0) {
					string subString = text.substr(last_pos,pos-last_pos);
					plusValue1=strSplitComma(subString);
				} 
				last_pos=pos+1;
			}
		}
	} else {
		vectorWords.push_back(0);
	}
	return  vectorWords;  //没有内容的时候
}

vector<int> ChangeTypeTool::strSplitComma (string text){
	int last_pos=0;
	string sep = ",";
	int pos=0;
	vector<int> vectorWords;
	if(text!=""&&text!=" ") {
		while(true){
			pos=text.find_first_of(sep,last_pos); //从最开始的字符位置0进行查找
			if(pos==string::npos){
				if(!text.substr(last_pos).empty()) {
					int value = ChangeTypeTool::stringToInt(text.substr(last_pos,pos-last_pos));
					vectorWords.push_back(value);
				}
				break;
			}else{
				if(pos-last_pos!=0) {
					int value = ChangeTypeTool::stringToInt(text.substr(last_pos,pos-last_pos));
					vectorWords.push_back(value);
					last_pos=pos+1;
				} else{
					last_pos=pos+1;
				}
			}
		}
	} else {
		vectorWords.push_back(0);
	}
	return vectorWords;
}
