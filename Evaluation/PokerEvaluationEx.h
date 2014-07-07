//
//  PokerEvaluationEx.h
//  pokerstove
//
//  Created by lys on 14-6-21.
//
//

#ifndef __pokerstove__PokerEvaluationEx__
#define __pokerstove__PokerEvaluationEx__

#include <stdio.h>
#include "PokerEvaluation.h"
    
#define CountArray(array) (sizeof(array)/sizeof(array[0]))

#define BYTE unsigned char
#define GAME_PLAYER 10
#define MAX_COUNT 2
#define MAX_CENTERCOUNT 5
#define FULL_COUNT  52

//扑克类型
enum{
    CT_EMPTY = -1,                                      //空类型
    CT_VIOLATIONS,                                      //违规类型
    CT_SINGLE,                                          //单牌类型
    CT_ONE_LONG,                                        //对子类型
    CT_TWO_LONG,                                        //两对类型
    CT_THREE_TIAO,                                      //三条类型
    CT_SHUN_ZI,                                         //顺子类型
    CT_TONG_HUA,                                        //同花类型
    CT_HU_LU,                                           //葫芦类型
    CT_TIE_ZHI,                                         //铁支类型
    CT_TONG_HUA_SHUN,									//同花顺型
    CT_KING_TONG_HUA_SHUN,                              //皇家同花顺
};

//分析结构
typedef struct
{
    unsigned char 							cbFourCount;                        //四张数目
    unsigned char 							cbThreeCount;                       //三张数目
    unsigned char 							cbLONGCount;                        //两张数目
    unsigned char							cbSignedCount;                      //单张数目
    unsigned char 							cbFourLogicVolue[1];				//四张列表
    unsigned char 							cbThreeLogicVolue[1];				//三张列表
    unsigned char 							cbLONGLogicVolue[2];				//两张列表
    unsigned char 							cbSignedLogicVolue[5];				//单张列表
    unsigned char							cbFourCardData[MAX_CENTERCOUNT];	//四张列表
    unsigned char							cbThreeCardData[MAX_CENTERCOUNT];	//三张列表
    unsigned char							cbLONGCardData[MAX_CENTERCOUNT];	//两张列表
    unsigned char							cbSignedCardData[MAX_CENTERCOUNT];	//单张数目
}tagAnalyseResult;


class PokerEvaluationEx : public PokerEvaluation
{
public:
    /**
     * @brief   获取牌型
     */
    static unsigned char cardType_Evaluation(unsigned char cbCardData[], unsigned char cbCardCount);
    /**
     * @brief   比牌
     * @pram
     * @return  unsigned char: 1:大于 -1:小于 0:等于
     */
    static int compare_Evaluation(unsigned char cbFirstData[], unsigned char cbNextData[], unsigned char cbCardCount);
    /**
     * @brief   分析牌型
     * @pram
     * @return
     */
    static void analysebCardData_Evaluation(const unsigned char cbCardData[], unsigned char cbCardCount, tagAnalyseResult *AnalyseResult);
    /**
     * @brief   获取牌型 - 扩展
     */
    static unsigned char cardTypeEx_Evaluation(unsigned char cbCardData[], unsigned char cbCardCount);
    /**
     * @brief   比牌 - 扩展
     * @pram
     * @return  unsigned char: 1:大于 -1:小于 0:等于
     */
    static int compareEx_Evaluation(unsigned char cbFirstData[], unsigned char cbNextData[], unsigned char cbCardCount);
    /**
     * @brief   尝试获取牌型
     */
    static int cardTypeTry_Evaluation(unsigned char cbCardData[], unsigned char cbCardCount);
};


#endif /* defined(__pokerstove__PokerEvaluationEx__) */
