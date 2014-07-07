//
//  ThreeCardEvaluation.cpp
//  TestCpp
//
//  Created by 罗耀生 on 14-6-21.
//
//

#include "ThreeCardEvaluation.h"
#include <stdio.h>

//豹子
//同花顺
//同花
//顺子
//对子
//单张
//特殊--当豹子存在时，“花色不同235”>“豹子” 即豹子存在时，若花色不同235也存在，花色不同235赢。 注：与豹子同时存在的不同花色235最大。（有的地方特殊仅仅大于三个A的豹子）
//一般拿到豹子和同花顺都有“喜钱”。
//逆时针开牌，相同牌，先开者输。

using namespace pokerstove;

int ThreeCardEvaluation::compare_Evaluation(unsigned char cbCardData1[], unsigned char cbCardData2[])
{
    int type1 = cardType_Evaluation( cbCardData1 );
    int type2 = cardType_Evaluation( cbCardData2 );
    
    if ( type1 > type2) {
        return 1;
    }else if ( type1 < type2) {
        return -1;
    }else{
        unsigned char ucValue1[3] = {0};
        unsigned char ucValue2[3] = {0};
        for (int idx = 0; idx < 3; idx++) {
            ucValue1[ idx ] = cardLogicValue_Evaluation( cbCardData1[ idx ] );
            ucValue2[ idx ] = cardLogicValue_Evaluation( cbCardData2[ idx ] );
        }
        
        sortCardList_Evaluation( ucValue1 , 3);
        sortCardList_Evaluation( ucValue2 , 3);
        
        int value = ucValue1[2] - ucValue2[2];
        if ( value > 0 ) {
            return 1;
        }else if( value < 0 ) {
            return -1;
        }else{
            return 0;
        }
    }
}

void ThreeCardEvaluation::ptf_type_Evaluation(unsigned char type)
{
    switch ( type) {
        case TeShu_3Card:
            printf("\n特殊\n");
            break;
        case DanZhang_3Card:
            printf("\n单张\n");
            break;
        case DuiZi_3Card:
            printf("\n对子\n");
            break;
        case ShunZi_3Card:
            printf("\n顺子\n");
            break;
        case TongHua_3Card:
            printf("\n同花\n");
            break;
        case TongHuaShun_3Card:
            printf("\n同花顺\n");
            break;
        case BaoZi_3Card:
            printf("\n豹子\n");
            break;
        default:
            break;
    }
}
