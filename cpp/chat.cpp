#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <string.h>
#include <sstream>


using namespace std;
char pic_path[200];

int count = 2;
class DetectResult{
public:
	int class_number;
	double x,y,w,h;
	DetectResult()=default;
	DetectResult(int c_,double x_,double y_,double w_,double h_):class_number(c_),x(x_),y(y_),w(w_),h(h_){}

};
const char* getPicture(){
	string str;
	cout<<"Please input picture name :";
	cin>>str;
	strcpy(pic_path,str.c_str());
	//ret[str.size()] = '\0';
	--count;
	return pic_path;
}

DetectResult result_parser(string &str){
	int dot = 0;
	int last = 0;
	int n = str.size(), count = 0;
	double result[5];
	string temp;
	while(dot < n ){
		if(str[dot] == ','){
			temp = str.substr(last,dot-last);
			result[count] = stod(temp);
			count++;
			last = ++dot;
		}
		else dot++;
	}
	temp = str.substr(last,dot-last);
	result[count] = stod(temp);
	return DetectResult(result[0],result[1],result[2],result[3],result[4]);
}

extern "C" {

	// if success, return true;
	int connect_camera(){
		if (true){
			return true;
		}
		else {
			return false;
		}
	}
	// return the path of picture
	const char* waitSource(){
		return getPicture();
		//return "";
	}

	// python give the result of detect.
	void sendResult(const char *result){
		//  ignore the bracket of result
		string res(result+1);
		res.pop_back();

		DetectResult temp = result_parser(res);
		cout<<temp.class_number<<','<<temp.x<<','<<temp.y<<','<<temp.w<<','<<temp.h<<endl;
		//cout<<res<<endl;
	}

	//finish ? if finish return true,else false;
	bool checkFinished(){
		return count;
		return true;
	}

	// disconnect, if success,return true;
	int disconnect_camera(){
		return true;
		//return false;
	}

}

