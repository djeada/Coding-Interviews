#include<iostream>

using namespace std;

int my_strlen(char *ptr);
void my_strncpy(char *ptr_dest, char *ptr_src, int n);

class CMyString {
	char* m_pData;
  	int length;  
	public:
		CMyString(){ 
			cout << "Default constructor.\n";
			m_pData = (char*)"Hello";
			length = my_strlen(m_pData);
		}

		CMyString(char* pData){ 
			cout << "myString( char * ) constr.\n";
			length = my_strlen(pData);
			my_strncpy(m_pData, pData, length );  // copy init value into storage
		}

		CMyString(const CMyString& str){
			cout << "myString copy const.\n";
			length = str.length;
			my_strncpy(m_pData, str.m_pData, length );
		}
			
		~CMyString(void){ 
			cout << "myString destr.\n";
			delete [] m_pData; 
		}
		
		CMyString& operator =(const CMyString &str){
			if(this != &str) {
				CMyString strTemp(str);
		
				char* pTemp = strTemp.m_pData;
				strTemp.m_pData = m_pData;
				m_pData = pTemp;
			}
			return *this;
		}

		int getLen() const{ return length; }
		friend ostream& operator<< (ostream& os, const CMyString& s);
};


ostream& operator<< (ostream& os, const CMyString &s) {
	int length = s.getLen();
	for(int i=0; i < length; i++){
		os.put(s.m_pData[i]);
	}
	return os;
}


int main(){
	CMyString a = (char*)"Hello ";
	CMyString b = a;
	CMyString c;

	cout << a << b << c << endl;

	return 0;
}

int my_strlen(char *ptr ){    
	int len = 0;
	char *p = ptr;
	while(*p != '\0' ) {
		len++;
		p++;
	}
	return len;
}

void my_strncpy( char * ptr_dest, char * ptr_src, int n ){
	for( int i=0; i < n; i++ ){
		ptr_dest[i] = ptr_src[i];
	}
}


