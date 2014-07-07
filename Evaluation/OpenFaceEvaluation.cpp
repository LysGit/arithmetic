//
//  OpenFaceEvaluation.cpp
//  TestCpp
//
//  Created by 罗耀生 on 14-6-21.
//
//

#include "OpenFaceEvaluation.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace pokerstove;

int cmp( const void *a , const void *b )
{
    return *(unsigned char *)a - *(unsigned char *)b;
}

int OpenFaceEvaluation::currscore_Evaluation(int user_count, int user_idx, unsigned char **ucTop, unsigned char **ucMid, unsigned char **ucLow){
    
    
    if ( user_idx >= user_count) {
        printf("数据出错！");
        return 0;
    }
    
    unsigned char ucTop_tag[5] = { 0 };
    unsigned char ucMid_tag[5] = { 0 };
    unsigned char ucLow_tag[5] = { 0 };
    
    for (int i = 0; i < 5; i++) {
        ucMid_tag[i] = ucMid[user_idx][i];
        ucLow_tag[i] = ucLow[user_idx][i];
        if ( i < 3) {
            ucTop_tag[i] = ucTop[user_idx][i];
        }
    }
    
    int *iType_tag = checkCardType_Evaluation( ucTop[ user_idx ], ucMid[ user_idx ], ucLow[ user_idx ] );
    
    int currscore = 0;
    
    for (int idx = 0; idx < user_count; idx++) {
        if ( idx == user_idx) {
            continue;
        }
        unsigned char ucTop_tmp[5] = { 0 };
        unsigned char ucMid_tmp[5] = { 0 };
        unsigned char ucLow_tmp[5] = { 0 };
        
        for (int i = 0; i < 5; i++) {
            ucMid_tmp[i] = ucMid[idx][i];
            ucLow_tmp[i] = ucLow[idx][i];
            if ( i < 3) {
                ucTop_tmp[i] = ucTop[idx][i];
            }
        }
        
        int *iType_tmp = checkCardType_Evaluation( ucTop_tmp, ucMid_tmp, ucLow_tmp );
        
        int iScoreTop = judgescore_Evaluation(5, ucTop_tag, ucTop_tmp, iType_tag[0], iType_tmp[0] );
        int iScoreMid = judgescore_Evaluation(5, ucMid_tag, ucMid_tmp, iType_tag[1], iType_tmp[1] );
        int iScoreLow = judgescore_Evaluation(5, ucLow_tag, ucLow_tmp, iType_tag[2], iType_tmp[2] );
        int iScore = iScoreTop+iScoreMid+iScoreLow;
        
        currscore += iScore;
    }
    return currscore;
}

int OpenFaceEvaluation::allKillScore_Evaluation(int user_count, int user_idx, unsigned char **ucTop, unsigned char **ucMid, unsigned char **ucLow){
    
    if ( user_idx >= user_count) {
        printf("数据出错！");
        return 0;
    }
    
    unsigned char ucTop_tag[5] = { 0 };
    unsigned char ucMid_tag[5] = { 0 };
    unsigned char ucLow_tag[5] = { 0 };
    
    for (int i = 0; i < 5; i++) {
        ucMid_tag[i] = ucMid[user_idx][i];
        ucLow_tag[i] = ucLow[user_idx][i];
        if ( i < 3) {
            ucTop_tag[i] = ucTop[user_idx][i];
        }
    }
    
    int *iType_tag = checkCardType_Evaluation( ucTop[ user_idx ], ucMid[ user_idx ], ucLow[ user_idx ] );
    
    int allKillscore = 0;
    
    for (int idx = 0; idx < user_count; idx++) {
        if ( idx == user_count) {
            continue;
        }
        unsigned char ucTop_tmp[5] = { 0 };
        unsigned char ucMid_tmp[5] = { 0 };
        unsigned char ucLow_tmp[5] = { 0 };
        
        for (int i = 0; i < 5; i++) {
            ucMid_tmp[i] = ucMid[idx][i];
            ucLow_tmp[i] = ucLow[idx][i];
            if ( i < 3) {
                ucTop_tmp[i] = ucTop[idx][i];
            }
        }
        
        int *iType_tmp = checkCardType_Evaluation( ucTop[ idx ], ucMid[ idx ], ucLow[ idx ] );
        int iScoreTop = judgescore_Evaluation(5, ucTop_tag, ucTop_tmp, iType_tag[0], iType_tmp[0] );
        int iScoreMid = judgescore_Evaluation(5, ucMid_tag, ucMid_tmp, iType_tag[1], iType_tmp[1] );
        int iScoreLow = judgescore_Evaluation(5, ucLow_tag, ucLow_tmp, iType_tag[2], iType_tmp[2] );
        int iScore = iScoreTop+iScoreMid+iScoreLow;
        if ( 3==iScore || -3==iScore) {
            allKillscore += iScore;
        }
    }
    return allKillscore;
}

int OpenFaceEvaluation::extrascore_Evaluation(unsigned char *ucTop, unsigned char *ucMid, unsigned char *ucLow){
    
    int *types = checkCardType_Evaluation( ucTop, ucMid, ucLow );

    //违规类型不记录统计
    if ( types[0] == CT_VIOLATIONS) {
        printf("AAA");
        return 0;
    }
    
    //玩家额外奖分
    int extrascoreTop = 0;
    int extrascoreMid = 0;
    int extrascoreLow = 0;
    
    //首道
    if ( CT_ONE_LONG == types[0] ) {
        
        int value = cardLogicValue_Evaluation( ucTop[1] );
        value = value - 5;
        value = (value<=0)?0:value;
        extrascoreTop = value;
    }else{
        extrascoreTop = 0;
    }
    
    //中道
    if ( types[1] != CT_VIOLATIONS) {
        switch ( types[1] ) {
            case CT_SHUN_ZI:
                extrascoreMid = 4;
                break;
                
            case CT_TONG_HUA:
                extrascoreMid = 8;
                break;
                
            case CT_HU_LU:
                extrascoreMid = 12;
                break;
                
            case CT_TIE_ZHI:
                extrascoreMid = 20;
                break;
                
            case CT_TONG_HUA_SHUN:
                extrascoreMid = 30;
                break;
                
            case CT_KING_TONG_HUA_SHUN:
                extrascoreMid = 50;
                break;
        }
    }else{
        extrascoreMid = 0;
    }
    
    //尾道
    if ( types[2] != CT_VIOLATIONS) {
        switch ( types[2] ) {
            case CT_SHUN_ZI:
                extrascoreLow = 2;
                break;
                
            case CT_TONG_HUA:
                extrascoreLow = 4;
                break;
                
            case CT_HU_LU:
                extrascoreLow = 6;
                break;
                
            case CT_TIE_ZHI:
                extrascoreLow = 10;
                break;
                
            case CT_TONG_HUA_SHUN:
                extrascoreLow = 15;
                break;
                
            case CT_KING_TONG_HUA_SHUN:
                extrascoreLow = 25;
                break;
        }
    }else{
        extrascoreLow = 0;
    }
    
    return (extrascoreTop+extrascoreMid+extrascoreLow);
}

int OpenFaceEvaluation::extrascore_Evaluation(int user_count, int user_idx, unsigned char **ucTop, unsigned char **ucMid, unsigned char **ucLow){
    
    
    int iReScore = 0;
    
    for (int idx = 0; idx < user_count; idx++ ) {
        int iScore = extrascore_Evaluation( ucTop[ idx ] , ucMid[ idx ], ucLow[ idx ]);
        
        if ( idx == user_idx ) {
            iReScore += iScore*(user_count-1);
        }else{
            iReScore -= iScore;
        }
    }
    return iReScore;
}

int OpenFaceEvaluation::sumscore_Evaluation(int user_count, int user_idx, unsigned char **ucTop, unsigned char **ucMid, unsigned char **ucLow){
    
    if ( user_idx >= user_count) {
        printf("数据出错！");
        return 0;
    }
    
    int currscore = currscore_Evaluation( user_count, user_idx, ucTop, ucMid, ucLow);
    int allscore = allKillScore_Evaluation( user_count, user_idx, ucTop, ucMid, ucLow);
    //    int extrascore = extrascore_Evaluation( ucTop[user_idx], ucMid[user_idx], ucLow[user_idx] );
    int extrascore = extrascore_Evaluation( user_count, user_idx, ucTop, ucMid, ucLow);
    
    return (currscore + allscore + extrascore);
}

int *OpenFaceEvaluation::checkCardType_Evaluation(unsigned char *ucTop, unsigned char *ucMid, unsigned char *ucLow){
    
    int *re = (int *)malloc( sizeof(int)*3 );
    memset( re, CT_EMPTY, sizeof(int)*3 );
    
    //玩家牌赋值 -- 要进行排序，所以新建
    unsigned char ucTop_tag[5] = { 0 };
    unsigned char ucMid_tag[5] = { 0 };
    unsigned char ucLow_tag[5] = { 0 };
    
    for (int i = 0; i < 5; i++) {
        ucMid_tag[i] = ucMid[i];
        ucLow_tag[i] = ucLow[i];
        if ( i < 3) {
            ucTop_tag[i] = ucTop[i];
        }
    }
    
    int typeTop = cardTypeTry_Evaluation(ucTop, 3);
    int typeMid = cardTypeTry_Evaluation(ucMid, 5);
    int typeLow = cardTypeTry_Evaluation(ucLow, 5);
    
    
    //修正类型
    if ( !( typeTop == CT_ONE_LONG || typeTop == CT_THREE_TIAO ) ) {
        typeTop = CT_SINGLE;
    }
    
    //违规类型修正
    if ( typeTop > typeMid || typeMid > typeLow || typeTop > typeLow) {
        typeTop = CT_VIOLATIONS;
        typeMid = CT_VIOLATIONS;
        typeLow = CT_VIOLATIONS;
    }
    
    //同一类型比较
    if ( typeTop == typeMid && typeMid != CT_VIOLATIONS) {
        int com = 0;
        if ( cardLogicValue_Evaluation(ucMid[0]) > cardLogicValue_Evaluation(ucTop[0]) ) {
            com = 2;
        }else if( cardLogicValue_Evaluation(ucMid[0]) == cardLogicValue_Evaluation(ucTop[0]) ){
            if ( cardLogicValue_Evaluation(ucMid[1]) > cardLogicValue_Evaluation(ucTop[1]) ) {
                com = 2;
            }else if ( cardLogicValue_Evaluation(ucMid[2]) > cardLogicValue_Evaluation(ucTop[2]) ){
                com = 2;
            }
        }
        if ( com < 2) {
            typeTop = CT_VIOLATIONS;
            typeMid = CT_VIOLATIONS;
            typeLow = CT_VIOLATIONS;
        }
    }
    if ( typeMid == typeLow && typeMid != CT_VIOLATIONS) {
        int com = compareEx_Evaluation( ucLow, ucMid, 5);
        if ( com < 2 ) {
            typeTop = CT_VIOLATIONS;
            typeMid = CT_VIOLATIONS;
            typeLow = CT_VIOLATIONS;
        }
    }
    
    re[0] = typeTop;
    re[1] = typeMid;
    re[2] = typeLow;
    
    return re;
}

int OpenFaceEvaluation::judgescore_Evaluation(int ucCount, unsigned char* uc1, unsigned char* uc2, int type1, int type2){
    
    int iScore = 0;
    
    int itypeTop = type1 - type2;
    if ( 0 == itypeTop) {
        if ( type1 == CT_VIOLATIONS ) {
            return 0;
        }
        
        int comp = compareEx_Evaluation(uc1, uc2, ucCount);
        switch ( comp ) {
            case 0:
                iScore = 0;
                break;
                
            case 1:
                iScore = -1;
                break;
                
            case 2:
                iScore = 1;
                break;
        }
    }else if ( itypeTop > 0){
        iScore = 1;
    }else{
        iScore = -1;
    }
    return iScore;
}

void OpenFaceEvaluation::ptf_type_Evaluation(unsigned char type)
{
    switch ( type ) {
        case CT_SINGLE:
            printf("单牌类型");
            break;
            
        case CT_ONE_LONG:
            printf("对子类型");
            break;
            
        case CT_TWO_LONG:
            printf("两对类型");
            break;
            
        case CT_THREE_TIAO:
            printf("三条类型");
            break;
            
        case CT_SHUN_ZI:
            printf("顺子类型");
            break;
            
        case CT_TONG_HUA:
            printf("同花类型");
            break;
            
        case CT_HU_LU:
            printf("葫芦类型");
            break;
            
        case CT_TIE_ZHI:
            printf("铁支类型");
            break;
            
        case CT_TONG_HUA_SHUN:
            printf("同花顺型");
            break;
            
        case CT_KING_TONG_HUA_SHUN:
            printf("皇家同花顺");
            break;
            
        case CT_VIOLATIONS:
            printf("违规");
            break;
            
        default:
            printf("出错");
            break;
    }
    printf("  ");
}
