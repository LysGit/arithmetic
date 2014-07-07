//
//  OpenFaceEvaluation.h
//  TestCpp
//
//  Created by 罗耀生 on 14-6-21.
//
//

#ifndef __TestCpp__OpenFaceEvaluation__
#define __TestCpp__OpenFaceEvaluation__

#include "PokerEvaluationEx.h"

namespace pokerstove
{
    class OpenFaceEvaluation : public PokerEvaluationEx{
    public:
        //针对服务器内容扩展封装 --- 后期可以考虑删除
        /**
         * @brief   比分结果：当前得分
         * @pram    user_count:玩家数
         user_idx:玩家索引
         * @return  int: 分数 -user_idx数据内容为空时，分数为0
         */
        static int currscore_Evaluation(int user_count, int user_idx, unsigned char **ucTop, unsigned char **ucMid, unsigned char **ucLow);
        /**
         * @brief   比分结果：通杀得分
         * @pram    user_count:玩家数
         user_idx:玩家索引
         * @return  int: 分数 -user_idx数据内容为空时，分数为0
         */
        static int allKillScore_Evaluation(int user_count, int user_idx, unsigned char **ucTop, unsigned char **ucMid, unsigned char **ucLow);
        /**
         * @brief   比分结果：额外得分
         * @pram    user_count:玩家数
         user_idx:玩家索引
         * @return  int: 分数 -user_idx数据内容为空时，分数为0
         */
        static int extrascore_Evaluation(unsigned char *ucTop, unsigned char *ucMid, unsigned char *cLow);
        
        /**
         * @brief   比分结果：额外得分
         * @pram    user_count:玩家数
         user_idx:玩家索引
         * @return  int: 分数 -user_idx数据内容为空时，分数为0
         */
        static int extrascore_Evaluation(int user_count, int user_idx, unsigned char **ucTop, unsigned char **ucMid, unsigned char **ucLow);
        
        /**
         * @brief   比分结果：总分
         * @pram    user_count:玩家数
         user_idx:玩家索引
         * @return  int: 分数 -user_idx数据内容为空时，分数为0
         */
        static int sumscore_Evaluation(int user_count, int user_idx, unsigned char **ucTop, unsigned char **ucMid, unsigned char **ucLow);
        
        /**
         * @brief   牌型获取比较
         * @return  int *: 按顶道，中道，底道返回类型 -- 当前不存在数据的为 -1
         */
        static int *checkCardType_Evaluation(unsigned char *ucTop, unsigned char *ucMid, unsigned char *ucLow);
        
        /**
         * @brief   （首，中，尾）道的分数
         * @pram
         * @return  int : 分数
         */
        static int judgescore_Evaluation(int ucCount, unsigned char* uc1, unsigned char* uc2, int type1, int type2);
        
        /**
         * @brief   打印牌型
         */
        static void ptf_type_Evaluation(unsigned char type);
        
    };
}

#endif /* defined(__TestCpp__OpenFaceEvaluation__) */
