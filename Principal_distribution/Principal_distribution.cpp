#include <iostream>
#include <map>
#include <string>
#include <Windows.h>
#include <list>
#include <vector>

using namespace std;

string ConvertThousandComma(int num, int commaPos = 3) {

    string str = to_string(num);
    string result;

    int len = str.length();
    int minus = commaPos - 1;

    for ( int i = len - 1; i >= 0; i -= commaPos ) {
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

int RandomMinMax(int min, int max) {
    int randNum = rand();
    if ( randNum > max ) {
        randNum %= max;
    }
    if ( randNum < min ) {
        randNum = min;
    }

    return randNum;
}

int main()
{
    srand((unsigned int)time(NULL));
    cout << "Hello World!" << endl;

    int oneGold;
    // code, price
    map<int, int> findJongmok;  // 코드, 가격
    map<int, int> myJongmok;    // 코드, 개수
    map<int, int> sellJongmok;  // 코드, 가격
    vector<int> selledVector;

    int menual = 0;
    int i = 0;

    cout << "원금은 얼마 : ";
    cin >> oneGold;

    while ( menual != -1 ) {
        // 랜덤한 종목을 선출, 랜덤한 종목 코드와 가격을 만들어내자 일단 개수부터
        cout << "==================== 찾은 종목 보여주자 ====================" << endl;
        int findCount = RandomMinMax(1, 50);
        for ( int i = 0; i < findCount; i++ ) {
            int code = RandomMinMax(1, 300);
            int price = RandomMinMax(1000, 500000);
            findJongmok.insert(pair<int, int>(code, price));
        }
        cout << "내가 찾은 종목 수 : " << findJongmok.size() << " 개" << endl;
        i = 0;
        for ( map<int, int>::iterator it = findJongmok.begin(); it != findJongmok.end(); it++, i++ ) {
            cout << i + 1 << ". code: " << it->first << "\t, 가격: " << it->second << " 원" << endl;
        }

        cout << endl << endl;
        cout << "==================== 팔 종목 보여주자 ====================" << endl;
        int sellCount = RandomMinMax(1, 50);
        for ( int i = 0; i < sellCount; i++ ) {
            int code = RandomMinMax(1, 300);
            int price = RandomMinMax(1000, 500000);
            sellJongmok.insert(pair<int, int>(code, price));
        }
        cout << "내가 팔아야 할 종목 수 : " << sellJongmok.size() << " 개" << endl;
        i = 0;
        for ( map<int, int>::iterator it = sellJongmok.begin(); it != sellJongmok.end(); it++, i++ ) {
            cout << i + 1 << ". code: " << it->first << "\t, 가격: " << it->second << " 원" << endl;
        }
        cout << endl << endl;

        // 찾은 종목을 코드를 담자
        int count = findJongmok.size();
        cout << "종목 찾았다 : " << count << " 개" << endl;

        int divideMoney = oneGold / count;
        cout << "분배 금액 : " << ConvertThousandComma(divideMoney) << " 원" << endl;

        map<int, int>::iterator iter;
        for ( iter = findJongmok.begin(); iter != findJongmok.end(); iter++ ) {
            // 몇개 살 건지 계산
            int codeCount = divideMoney / iter->second;
            int buyCount = 0;

            if ( codeCount > 1000 ) { // 1000 개 넘으면 1000개로 맞춰줌
                buyCount = 1000;
            }
            else if ( codeCount < 1 ) // 하나도 못살 가격이면 사지마
                continue;
            else {
                buyCount = codeCount; // 이외엔 그냥 사자
            }

            // 시장가로 걍 사자
            // 실행!
            if ( buyCount > 0 ) {
                myJongmok.insert(pair<int, int>(iter->first, buyCount));
                cout << iter->second << "원 짜리 " << ConvertThousandComma(buyCount) << "개 샀다, 총 금액: " << ConvertThousandComma(iter->second * buyCount) << " 원" << endl;
                //Sleep(1000);
            }

            oneGold -= (buyCount * iter->second);
        }

        cout << endl << "한바퀴 돌고 난 후 원금 가격 : " << ConvertThousandComma(oneGold) << " 원" << endl;

        cout << "내가 산 종목 코드랑 몇 주 샀는지 보여줄게 " << endl << endl;
        i = 0; 
        for ( iter = myJongmok.begin(); iter != myJongmok.end(); iter++, i++ ) {
            cout << i + 1 << ". 코드: " << iter->first << "\t산 개수: " << iter->second << endl;
            //Sleep(1000);
        }
        i = 0;
        cout << "이제 팔아야 할 종목들이 내 거에 있는지 검사해서 팔자" << endl;
        cout << "팔아야할 종목들 보여줄게" << endl;
        for ( iter = sellJongmok.begin(); iter != sellJongmok.end(); iter++, i++ ) {
            cout << i + 1 << ". 팔아야 할 코드: " << iter->first << endl;
            //Sleep(1000);
        }

        // 내가 가지고 있는 것들 중에서 팔아야 할 코드를 보여주자
        for ( iter = myJongmok.begin(); iter != myJongmok.end(); iter++ ) {
            for ( map<int, int>::iterator iter2 = sellJongmok.begin(); iter2 != sellJongmok.end(); iter2++ ) {
                if ( iter->first == iter2->first ) {
                    cout << "똑같은 코드니까 이거 팔자: " << iter->first << endl;
                    //Sleep(1000);
                    selledVector.push_back(iter->first);
                    oneGold += iter2->second * iter->second;
                    break;
                }
                else if ( iter->first < iter2->first ) {  // map은 자동 정렬에 되어 있는 상태니까
                    break;
                }
            }
        }

        iter = myJongmok.begin();
        for ( int i = 0; i < selledVector.size(); i++ ) {
            myJongmok.erase(selledVector[i]);
        }
        
        // 장 마감시간 다가오면 전부 다 팔아버리자 남아있는 애들 뭐가 있니?
        cout << "장 마감시간 다가오면 전부 다 팔아버리자 남아있는 애들 뭐가 있니?" << endl;
        i = 0;
        for ( iter = myJongmok.begin(); iter != myJongmok.end(); iter++, i++ ) {
            cout << i + 1 << ". 코드 번호 : " << iter->first << "\t, 판 가격: " << findJongmok[iter->first] * iter->second << " 원" << endl;
            oneGold += findJongmok[iter->first] * iter->second;
            oneGold -= (int)((findJongmok[iter->first] * iter->second) * 0.015);
        }

        cout << "가격이 변해서 판 개수: " << selledVector.size() << "\t, 그냥 제 가격에 판 개수: " << myJongmok.size() << endl;
        cout << "모두 완료 하고 난 후의 원금 가격 : " << ConvertThousandComma(oneGold) << endl;
        myJongmok.clear();
        findJongmok.clear();
        sellJongmok.clear();
        selledVector.clear();


        cout << endl << "종료 하려면 -1 입력 : ";
        cin >> menual;
    }


    

    return 0;
}