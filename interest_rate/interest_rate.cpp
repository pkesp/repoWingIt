@@ -0,0 +1,74 @@
﻿// Interest rate.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <string>

using namespace std;

string ConvertThousandComma(int num, int commaPos = 3) {

    string str = to_string(num);
    string result;

    int len = str.length();
    int minus = commaPos - 1;

    for ( int i = len - 1; i >= 0; i-= commaPos ) {
        if ( i - minus > 0 ) {
            auto temp = str.substr(i - minus, commaPos);
            result.insert(0, str.substr(i - minus, commaPos));
            result.insert(0, ",");
        }
        else {
			result.insert(0, str.substr(0, i + 1));
        }
    }

    return result;
}

int main()
{
    std::cout << "Hello World!" << std::endl;

    int onegold;
    float rate;
    int day, month = 0;
    int menual = 0;

    while ( menual != -1 ) {
        cout << "원금 얼마 : ";
        cin >> onegold;
        cout << "이율 얼마 : ";
        cin >> rate;
        cout << "며칠 동안 : ";
        cin >> day;

        if ( day == 0 ) {
            cout << "몇 달 동안 : ";
            cin >> month;
        }

        if ( day != 0 ) {
            for ( int i = 0; i < day; i++ ) {
                onegold += (onegold * rate);
                printf("%d 번째 원금 : %s\n", i + 1, ConvertThousandComma(onegold).c_str());
            }
        }
        else {
            int totalDay = month * 25;
            for ( int i = 0; i < totalDay; i++ ) {
                onegold += (onegold * rate);
                printf("%d 번째 원금 : %s\n", i + 1, ConvertThousandComma(onegold).c_str());
            }
        }

        cout << endl << endl;
        cout << "끝내려면 -1 입력 : ";
        cin >> menual;
        cout << endl << endl;
    }

    return 0;
}
