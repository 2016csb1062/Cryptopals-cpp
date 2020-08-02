#include<iostream>
#include<unordered_map>
#include<math.h>
#include"map_helper.cpp"
#include<string>

using namespace std;

class CONSTANTS
{
    public:
        char binaryChars[2] = {'0','1'};
        char hexChars[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
        char base64Chars[64] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                                'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                                '0','1','2','3','4','5','6','7','8','9','+','/'};
        unordered_map <string,char> binary2base64_map;
        unordered_map <string,char> binary2hex_map;
        unordered_map <char,string> hex2binary_map;
        unordered_map <char,string> base642binary_map;
        CONSTANTS()
        {
            this->binary2base64_map = map_binary2base(64);
            this->binary2hex_map = map_binary2base(16);
            this->hex2binary_map = reverse_map(this->binary2hex_map);
            this->base642binary_map = reverse_map(this->binary2base64_map);
        }
        
        char * getBaseChars(int base)
        {
            if (base ==2) return this->binaryChars;
            else if (base == 16) return this->hexChars;
            else if (base == 64) return this->base64Chars;
            else NULL;
        }

        unordered_map <string,char> getBin2Base_map(int base)
        {
            if (base == 16) return this->binary2hex_map;
            else if (base == 64) return this->binary2base64_map;
        }
        unordered_map <char,string> getBase2Bin_map(int base)
        {
            if (base == 16) return this->hex2binary_map;
            else if (base == 64) return this->base642binary_map;
        }

        unordered_map <string,char> map_binary2base(int base)
        {
            int numOfBinChar = log2(base);
            string binary;
            for (int i=0; i<numOfBinChar; i++)
            {
                binary += '1';
            }
            char * baseChars = getBaseChars(base);
            unordered_map <string,char> binary2base_map;
            for(int i = 0 ; i < base ; i++)
            {
                bool inProcess = true;
                int current_digit = numOfBinChar-1;
                while(inProcess&& current_digit>=0 )
                {
                    if(binary[current_digit] =='1')
                    {
                        binary[current_digit] = '0';
                        current_digit--;
                    }
                    else
                    {
                        binary[current_digit] = '1';
                        inProcess=false;
                    }
                }
                binary2base_map[binary] = baseChars[i];
                //cout<<binary<<":"<<baseChars[i]<<endl;
            }
            return binary2base_map;
        }

        template<typename a , typename b>
        unordered_map<b,a> reverse_map(unordered_map<a,b> map)
        {
            typename unordered_map<a,b>::iterator itr = map.begin();
            unordered_map<b,a> new_map;
            while(itr!=map.end())
            {
                new_map[itr->second] = itr->first;
                itr++;
            }
            return new_map;
        }
};

class Converter
{
    CONSTANTS constants;
    string base2binary(string hex, int base)
    {
        string binary = "";
        unordered_map<char,string> base2bin_map = constants.getBase2Bin_map(base);
        for(char i : hex)
        {
            binary+=base2bin_map[i];
        }
        return binary;
    }
    string binary2base(string binary, int base)
    {
        int numOfBinChar = log2(base);
        string base_string = "";
        unordered_map <string,char> bin2base_map = constants.getBin2Base_map(base);
        if (binary.size()%numOfBinChar != 0){
            throw -1;
        }
        for(int i= 0 ; i< binary.size() ; i+=numOfBinChar)
        {
            base_string+= bin2base_map[binary.substr(i,numOfBinChar)];
        }
        return base_string;
    }
    
    public:
    Converter()
    {
        constants = CONSTANTS();
    }
    string hex2binary(string hex)
    {
        return base2binary(hex,16);
    }
    string base642binary(string hex)
    {
        return base2binary(hex,64);
    }
    string binary2hex(string binary)
    {
        return binary2base(binary,16);
    }
    string binary2base64(string binary)
    {
        return binary2base(binary,64);
    }
    string hex2base64(string hex)
    {
        return binary2base64(hex2binary(hex));
    }
    string base642hex(string base64)
    {
        return binary2hex(base642binary(base64));
    }
    
};

int main()
{
    Converter c = Converter();
    cout<<c.hex2base64("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d")<<endl;
}