//
//  ThreeCardEvaluation.h
//  TestCpp
//
//  Created by 罗耀生 on 14-6-21.
//
//

#ifndef __TestCpp__ThreeCardEvaluation__
#define __TestCpp__ThreeCardEvaluation__

#include "PokerEvaluation.h"

namespace pokerstove
{
    enum
    {
        TeShu_3Card = 0,
        DanZhang_3Card,
        DuiZi_3Card,///
        ShunZi_3Card,
        TongHua_3Card,
        TongHuaShun_3Card,
        BaoZi_3Card
    };
    
    class ThreeCardEvaluation :public PokerEvaluation{
    public:
        /**
         * @brief   获取牌型
         * @pram    cbCardData[]:牌数组
         * @return  unsigned char: 获取牌型
         */
        static unsigned char cardType_Evaluation(unsigned char cbCardData[]);
        /**
         * @brief   比较大小 -- 不考虑先后翻牌情况
         * @pram    玩家牌数组
         * @return  int: 1: cbCardData1 > cbCardData2  0: cbCardData1 == cbCardData2
         */
        static int compare_Evaluation(unsigned char cbCardData1[], unsigned char cbCardData2[]);
        /**
         * @brief   打印牌型
         */
        static void ptf_type_Evaluation(unsigned char type);
    };
}

#endif /* defined(__TestCpp__ThreeCardEvaluation__) */
