//
//  PokerEvaluationEx.cpp
//  pokerstove
//
//  Created by lys on 14-6-21.
//
//

#include "PokerEvaluationEx.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>


int cmp( const void *a , const void *b )
{
    return *(unsigned char *)a - *(unsigned char *)b;
}

unsigned char PokerEvaluationEx::cardType_Evaluation(unsigned char cbCardData[], unsigned char cbCardCount)
{
    //数据校验
	assert(cbCardCount == MAX_CENTERCOUNT);
	if(cbCardCount !=MAX_CENTERCOUNT) return 0;
    
	//变量定义
	unsigned char cbSameColor = 1,bLineCard = 1;
	unsigned char cbFirstColor = cardColor_Evaluation(cbCardData[0]);
	unsigned char cbFirstValue = cardLogicValue_Evaluation(cbCardData[0]);
    
	//牌形分析
	for (unsigned char i=1;i < cbCardCount;i++)
	{
		//数据分析
		if ( cardColor_Evaluation(cbCardData[i])!=cbFirstColor) cbSameColor=0;
		if (cbFirstValue!=( cardLogicValue_Evaluation(cbCardData[i])+i)) bLineCard=0;
        
		//结束判断
		if ((cbSameColor==0)&&(bLineCard==0)) break;
	}
    
	//最小同花顺
	if((bLineCard == 0)&&(cbFirstValue == 14))
	{
		unsigned char i=1;
		for (i=1;i < cbCardCount;i++)
		{
			unsigned char cbLogicValue = cardLogicValue_Evaluation(cbCardData[i]);
			if ((cbFirstValue!=(cbLogicValue+i+8)))break;
		}
		if( i == cbCardCount)
			bLineCard = 1;
        
	}
    
	//皇家同花顺
	if ((cbSameColor==1)&&(bLineCard==1)&&( cardLogicValue_Evaluation(cbCardData[1]) ==13 ))
		return CT_KING_TONG_HUA_SHUN;
    
	//顺子类型
	if ((cbSameColor==0)&&(bLineCard==1))
		return CT_SHUN_ZI;
    
	//同花类型
	if ((cbSameColor==1)&&(bLineCard==0))
		return CT_TONG_HUA;
    
	//同花顺类型
	if ((cbSameColor==1)&&(bLineCard==1))
		return CT_TONG_HUA_SHUN;
    
	//扑克分析
	tagAnalyseResult AnalyseResult;
	analysebCardData_Evaluation(cbCardData,cbCardCount,&AnalyseResult);
    
	//类型判断
	if (AnalyseResult.cbFourCount==1)
		return CT_TIE_ZHI;
	if (AnalyseResult.cbLONGCount==2)
		return CT_TWO_LONG;
	if ((AnalyseResult.cbLONGCount==1)&&(AnalyseResult.cbThreeCount==1))
		return CT_HU_LU;
	if ((AnalyseResult.cbThreeCount==1)&&(AnalyseResult.cbLONGCount==0))
		return CT_THREE_TIAO;
	if ((AnalyseResult.cbLONGCount==1)&&(AnalyseResult.cbSignedCount==3))
		return CT_ONE_LONG;
    
	return CT_SINGLE;
}

int PokerEvaluationEx::compare_Evaluation(unsigned char cbFirstData[], unsigned char cbNextData[], unsigned char cbCardCount)
{
    //获取类型
	unsigned char cbNextType = cardTypeEx_Evaluation(cbNextData,cbCardCount);
	unsigned char cbFirstType = cardTypeEx_Evaluation(cbFirstData,cbCardCount);
    
	//类型判断
	//大
	if(cbFirstType>cbNextType)
		return 1;
    
	//小
	if(cbFirstType<cbNextType)
		return -1;
    
	//简单类型
	switch(cbFirstType)
	{
        case CT_SINGLE:			//单牌
		{
			//对比数值
			unsigned char i=0;
			for (i=0;i<cbCardCount;i++)
			{
				unsigned char cbNextValue = cardLogicValue_Evaluation(cbNextData[i]);
				unsigned char cbFirstValue = cardLogicValue_Evaluation(cbFirstData[i]);
                
				//大
				if(cbFirstValue > cbNextValue)
					return 1;
				//小
				else if(cbFirstValue <cbNextValue)
					return -1;
				//等
				else
					continue;
			}
			//平
			if( i == cbCardCount)
				return 0;
            
			assert(0);
		}
        case CT_ONE_LONG:		//对子
        case CT_TWO_LONG:		//两对
        case CT_THREE_TIAO:		//三条
        case CT_TIE_ZHI:		//铁支
        case CT_HU_LU:			//葫芦
		{
			//分析扑克
			tagAnalyseResult AnalyseResultNext;
			tagAnalyseResult AnalyseResultFirst;
			analysebCardData_Evaluation(cbNextData,cbCardCount,&AnalyseResultNext);
			analysebCardData_Evaluation(cbFirstData,cbCardCount,&AnalyseResultFirst);
            
			//四条数值
			if (AnalyseResultFirst.cbFourCount>0)
			{
				unsigned char cbNextValue=AnalyseResultNext.cbFourLogicVolue[0];
				unsigned char cbFirstValue=AnalyseResultFirst.cbFourLogicVolue[0];
                
				//比较四条
				if(cbFirstValue != cbNextValue)return (cbFirstValue > cbNextValue)?1:-1;
                
				//比较单牌
				assert(AnalyseResultFirst.cbSignedCount==1 && AnalyseResultNext.cbSignedCount==1);
				cbFirstValue = AnalyseResultFirst.cbSignedLogicVolue[0];
				cbNextValue = AnalyseResultNext.cbSignedLogicVolue[0];
				if(cbFirstValue != cbNextValue)return (cbFirstValue > cbNextValue)?1:-1;
				else return 0;
			}
            
			//三条数值
			if (AnalyseResultFirst.cbThreeCount>0)
			{
				unsigned char cbNextValue=AnalyseResultNext.cbThreeLogicVolue[0];
				unsigned char cbFirstValue=AnalyseResultFirst.cbThreeLogicVolue[0];
                
				//比较三条
				if(cbFirstValue != cbNextValue)return (cbFirstValue > cbNextValue)?1:-1;
                
				//葫芦牌型
				if(CT_HU_LU == cbFirstType)
				{
					//比较对牌
					assert(AnalyseResultFirst.cbLONGCount==1 && AnalyseResultNext.cbLONGCount==1);
					cbFirstValue = AnalyseResultFirst.cbLONGLogicVolue[0];
					cbNextValue = AnalyseResultNext.cbLONGLogicVolue[0];
					if(cbFirstValue != cbNextValue)return (cbFirstValue > cbNextValue)?1:-1;
					else return 0;
				}
				else //三条带单
				{
					//比较单牌
					assert(AnalyseResultFirst.cbSignedCount==2 && AnalyseResultNext.cbSignedCount==2);
                    
					//散牌数值
					unsigned char i=0;
					for (i=0;i<AnalyseResultFirst.cbSignedCount;i++)
					{
						unsigned char cbNextValue=AnalyseResultNext.cbSignedLogicVolue[i];
						unsigned char cbFirstValue=AnalyseResultFirst.cbSignedLogicVolue[i];
						//大
						if(cbFirstValue > cbNextValue)
							return 1;
						//小
						else if(cbFirstValue < cbNextValue)
							return -1;
						//等
						else continue;
					}
					if( i == AnalyseResultFirst.cbSignedCount)
						return 0;
					assert(0);
				}
			}
            
			//对子数值
			unsigned char i=0;
			for ( i=0;i<AnalyseResultFirst.cbLONGCount;i++)
			{
				unsigned char cbNextValue=AnalyseResultNext.cbLONGLogicVolue[i];
				unsigned char cbFirstValue=AnalyseResultFirst.cbLONGLogicVolue[i];
				//大
				if(cbFirstValue > cbNextValue)
					return 1;
				//小
				else if(cbFirstValue <cbNextValue)
					return -1;
				//平
				else
					continue;
			}
            
			//比较单牌
			assert( i == AnalyseResultFirst.cbLONGCount);
			{
				assert(AnalyseResultFirst.cbSignedCount==AnalyseResultNext.cbSignedCount
                       && AnalyseResultNext.cbSignedCount>0);
				//散牌数值
				for (i=0;i<AnalyseResultFirst.cbSignedCount;i++)
				{
					unsigned char cbNextValue=AnalyseResultNext.cbSignedLogicVolue[i];
					unsigned char cbFirstValue=AnalyseResultFirst.cbSignedLogicVolue[i];
					//大
					if(cbFirstValue > cbNextValue)
						return 1;
					//小
					else if(cbFirstValue <cbNextValue)
						return -1;
					//等
					else continue;
				}
				//平
				if( i == AnalyseResultFirst.cbSignedCount)
					return 0;
			}
			break;
		}
        case CT_SHUN_ZI:		//顺子
        case CT_TONG_HUA_SHUN:	//同花顺
		{
			//数值判断
			unsigned char cbNextValue = cardLogicValue_Evaluation(cbNextData[0]);
			unsigned char cbFirstValue = cardLogicValue_Evaluation(cbFirstData[0]);
            
			unsigned char bFirstmin= (cbFirstValue ==(cardLogicValue_Evaluation(cbFirstData[1])+9));
			unsigned char bNextmin= (cbNextValue ==(cardLogicValue_Evaluation(cbNextData[1])+9));

			//大小顺子
			if ((bFirstmin==1)&&(bNextmin == 0))
			{
                if ( cardValue_Evaluation( cbFirstData[0] ) == 1 && cardValue_Evaluation( cbNextData[0] ) != 13 &&  cardValue_Evaluation( cbNextData[0] ) != 1 ) {
                    return 1;
                }
                
				return -1;
			}
            
			//大小顺子
			else if ((bFirstmin==0)&&(bNextmin == 1))
			{
                if (  cardValue_Evaluation( cbNextData[0] ) == 1 && cardValue_Evaluation( cbFirstData[0] ) != 13 &&  cardValue_Evaluation( cbFirstData[0] ) != 1 ){
                    return -1;
                }
				return 1;
			}
            
			//等同顺子
			else
			{
				//平
				if(cbFirstValue == cbNextValue)return 0;
				return (cbFirstValue > cbNextValue)?2:1;
			}
		}
        case CT_TONG_HUA:		//同花
		{
			//散牌数值
            unsigned char i=0;
			for (i=0;i<cbCardCount;i++)
			{
				unsigned char cbNextValue = cardLogicValue_Evaluation(cbNextData[i]);
				unsigned char cbFirstValue = cardLogicValue_Evaluation(cbFirstData[i]);
				if(cbFirstValue == cbNextValue)continue;
				return (cbFirstValue > cbNextValue)?1:-1;
			}
			//平
			if( i == cbCardCount) return 0;  //这边
		}
	}
    
	return  0;
}

void PokerEvaluationEx::analysebCardData_Evaluation(const unsigned char cbCardData[], unsigned char cbCardCount, tagAnalyseResult *AnalyseResult)
{
    //设置结果
    memset(AnalyseResult, 0, sizeof(*AnalyseResult));
	
	//扑克分析
	for (unsigned char i=0;i<cbCardCount;i++)
	{
		//变量定义
		unsigned char cbSameCount=1;
		unsigned char cbSameCardData[4]={cbCardData[i],0,0,0};
		unsigned char cbLogicValue = cardLogicValue_Evaluation(cbCardData[i]);
        
		//获取同牌
		for (int j=i+1;j<cbCardCount;j++)
		{
			//逻辑对比
			if ( cardLogicValue_Evaluation(cbCardData[j])!=cbLogicValue) break;
            
			//设置扑克
			cbSameCardData[cbSameCount++]=cbCardData[j];
		}
        
		//保存结果
		switch (cbSameCount)
		{
            case 1:		//单张
			{
				AnalyseResult->cbSignedLogicVolue[AnalyseResult->cbSignedCount]=cbLogicValue;
                memcpy(&AnalyseResult->cbSignedCardData[(AnalyseResult->cbSignedCount++)*cbSameCount],cbSameCardData,cbSameCount);
				break;
			}
            case 2:		//两张
			{
				AnalyseResult->cbLONGLogicVolue[AnalyseResult->cbLONGCount]=cbLogicValue;
                memcpy(&AnalyseResult->cbLONGCardData[(AnalyseResult->cbLONGCount++)*cbSameCount],cbSameCardData,cbSameCount);
				break;
			}
            case 3:		//三张
			{
				AnalyseResult->cbThreeLogicVolue[AnalyseResult->cbThreeCount]=cbLogicValue;
                memcpy(&AnalyseResult->cbThreeCardData[(AnalyseResult->cbThreeCount++)*cbSameCount],cbSameCardData,cbSameCount);
				break;
			}
            case 4:		//四张
			{
				AnalyseResult->cbFourLogicVolue[AnalyseResult->cbFourCount]=cbLogicValue;
                memcpy(&AnalyseResult->cbFourCardData[(AnalyseResult->cbFourCount++)*cbSameCount],cbSameCardData,cbSameCount);
				break;
			}
		}
        
		//设置递增
		i+=cbSameCount-1;
	}
    
	return;
}

unsigned char PokerEvaluationEx::cardTypeEx_Evaluation(unsigned char cbCardData[], unsigned char cbCardCount)
{
	if(MAX_CENTERCOUNT == cbCardCount)
		return cardType_Evaluation(cbCardData, cbCardCount);
	else if(cbCardCount <= 0 || cbCardCount > MAX_CENTERCOUNT)
		return 0;
    
	//下面是针对2-4张牌的牌型判定 4条>3条>两对>一对>高牌
	//扑克分析
	tagAnalyseResult AnalyseResult;
	analysebCardData_Evaluation(cbCardData,cbCardCount,&AnalyseResult);
    
	//类型判断
	if (AnalyseResult.cbFourCount==1)
		return CT_TIE_ZHI;
	if (AnalyseResult.cbLONGCount==2)
		return CT_TWO_LONG;
    //	if ((AnalyseResult.cbLONGCount==1)&&(AnalyseResult.cbThreeCount==1))
    //		return CT_HU_LU;
	if ((AnalyseResult.cbThreeCount==1)&&(AnalyseResult.cbLONGCount==0))
		return CT_THREE_TIAO;
	if (AnalyseResult.cbLONGCount==1)//if ((AnalyseResult.cbLONGCount==1)&&(AnalyseResult.cbSignedCount==3))
		return CT_ONE_LONG;
    
	return CT_SINGLE;
}

int PokerEvaluationEx::compareEx_Evaluation(unsigned char cbFirstData[], unsigned char cbNextData[], unsigned char cbCardCount)
{
	if(MAX_CENTERCOUNT == cbCardCount)
		return compare_Evaluation(cbFirstData, cbNextData, cbCardCount);
	
	//下面是针对2-4张牌的判定
	
    //获取类型
	unsigned char cbNextType = cardTypeEx_Evaluation(cbNextData,cbCardCount);
	unsigned char cbFirstType = cardTypeEx_Evaluation(cbFirstData,cbCardCount);
    
	//类型判断
	//大
	if(cbFirstType>cbNextType)
		return 1;
    
	//小
	if(cbFirstType<cbNextType)
		return -1;
    
	//简单类型
	switch(cbFirstType)
	{
        case CT_SINGLE:			//单牌
		{
			//对比数值
			unsigned char i=0;
			for (i=0;i<cbCardCount;i++)
			{
				unsigned char cbNextValue = cardLogicValue_Evaluation(cbNextData[i]);
				unsigned char cbFirstValue = cardLogicValue_Evaluation(cbFirstData[i]);
                
				//大
				if(cbFirstValue > cbNextValue)
					return 1;
				//小
				else if(cbFirstValue <cbNextValue)
					return -1;
				//等
				else
					continue;
			}
			//平
			if( i == cbCardCount)
				return 0;
            
			assert(0);
		}
        case CT_ONE_LONG:		//对子
        case CT_TWO_LONG:		//两对
        case CT_THREE_TIAO:		//三条
        case CT_TIE_ZHI:		//铁支
            //case CT_HU_LU:			//葫芦
		{
			//分析扑克
			tagAnalyseResult AnalyseResultNext;
			tagAnalyseResult AnalyseResultFirst;
			analysebCardData_Evaluation(cbNextData,cbCardCount,&AnalyseResultNext);
			analysebCardData_Evaluation(cbFirstData,cbCardCount,&AnalyseResultFirst);
            
			//四条数值
			if (AnalyseResultFirst.cbFourCount>0)
			{
				unsigned char cbNextValue=AnalyseResultNext.cbFourLogicVolue[0];
				unsigned char cbFirstValue=AnalyseResultFirst.cbFourLogicVolue[0];
                
				//比较四条
				if(cbFirstValue != cbNextValue)return (cbFirstValue > cbNextValue)?1:-1;
			}
            
			//三条数值
			if (AnalyseResultFirst.cbThreeCount>0)
			{
				unsigned char cbNextValue=AnalyseResultNext.cbThreeLogicVolue[0];
				unsigned char cbFirstValue=AnalyseResultFirst.cbThreeLogicVolue[0];
                
				//比较三条
				if(cbFirstValue != cbNextValue)return (cbFirstValue > cbNextValue)?2:1;
                
                //散牌数值
                unsigned char i=0;
                for (i=0;i<AnalyseResultFirst.cbSignedCount;i++)
                {
                    unsigned char cbNextValue=AnalyseResultNext.cbSignedLogicVolue[i];
                    unsigned char cbFirstValue=AnalyseResultFirst.cbSignedLogicVolue[i];
                    //大
                    if(cbFirstValue > cbNextValue)
                        return 1;
                    //小
                    else if(cbFirstValue < cbNextValue)
                        return -1;
                    //等
                    else continue;
                }
                if( i == AnalyseResultFirst.cbSignedCount)
                    return 0;
                assert(0);
                //				}
			}
            
			//对子数值
			unsigned char i=0;
			for ( i=0;i<AnalyseResultFirst.cbLONGCount;i++)
			{
				unsigned char cbNextValue=AnalyseResultNext.cbLONGLogicVolue[i];
				unsigned char cbFirstValue=AnalyseResultFirst.cbLONGLogicVolue[i];
				//大
				if(cbFirstValue > cbNextValue)
					return 1;
				//小
				else if(cbFirstValue <cbNextValue)
					return -1;
				//平
				else
					continue;
			}
            
			//比较单牌
			assert( i == AnalyseResultFirst.cbLONGCount);
			{
				assert(AnalyseResultFirst.cbSignedCount==AnalyseResultNext.cbSignedCount);
				if(0 == AnalyseResultNext.cbSignedCount)
					return 0;
				
				//散牌数值
				for (i=0;i<AnalyseResultFirst.cbSignedCount;i++)
				{
					unsigned char cbNextValue=AnalyseResultNext.cbSignedLogicVolue[i];
					unsigned char cbFirstValue=AnalyseResultFirst.cbSignedLogicVolue[i];
					//大
					if(cbFirstValue > cbNextValue)
						return 1;
					//小
					else if(cbFirstValue <cbNextValue)
						return -1;
					//等
					else continue;
				}
				//平
				if( i == AnalyseResultFirst.cbSignedCount)
					return 0;
			}
			break;
		}
		default:
			break;
	}
    
	return  0;
}

int PokerEvaluationEx::cardTypeTry_Evaluation(unsigned char cbCardData[], unsigned char cbCardCount)
{
    if ( cbCardCount < 2 || cbCardCount > 5) {
        return CT_EMPTY;
    }
    
    
    unsigned char cbCardData_tag[5] = { 0 };
    for (int i = 0; i < cbCardCount; i++) {
        cbCardData_tag[i] = cbCardData[i];
    }
    sortCardList_Evaluation( cbCardData_tag, cbCardCount);
    
    unsigned char value[5] = { 0 };
    unsigned char color[5] = { 0 };
    
    unsigned char value_qsort[5] = { 0 };
    unsigned char color_qsort[5] = { 0 };
    
    unsigned char value_qsort_A[5] = { 0 };
    
    for ( int i = 0; i < 5; i++) {
        if ( i < cbCardCount) {
            value[i] = cardValue_Evaluation( cbCardData[i] );
            color[i] = cardColor_Evaluation( cbCardData[i] );
            
            value_qsort[i] = value[i];
            color_qsort[i] = color[i];
            
            value_qsort_A[i] = value_qsort[i]==1?14:value_qsort[i];
        }
    }
    
    qsort( value_qsort, cbCardCount, sizeof( value_qsort[0] ), cmp);
    qsort( color_qsort, cbCardCount, sizeof( color_qsort[0] ), cmp);
    qsort( value_qsort_A, cbCardCount, sizeof( value_qsort_A[0] ), cmp);
    
    
    switch ( cbCardCount ) {
        case 2:
        {
            if ( value_qsort[0] == value_qsort[1] ) {
                return CT_ONE_LONG;
            }
        }
            break;
        case 3:
        {
            //3张开始需要预测顺子
            if( color_qsort[0] == color_qsort[1] && color_qsort[1] == color_qsort[2] ){
                if ( value_qsort[2] - value_qsort[0] <= 4 && !(value_qsort[0] == value_qsort[1] || value_qsort[1] == value_qsort[2]) ) {
                    return CT_TONG_HUA_SHUN;
                }
                
                if ( value_qsort_A[2] - value_qsort_A[0] <= 4 && !(value_qsort_A[0] == value_qsort_A[1] || value_qsort_A[1] == value_qsort_A[2]) ) {
                    return CT_TONG_HUA_SHUN;
                }
                
                return CT_TONG_HUA;
            }else if ( value_qsort[0] == value_qsort[1] || value_qsort[1] == value_qsort[2]) {
                if ( value_qsort[0] == value_qsort[1] && value_qsort[1] == value_qsort[2]) {
                    return CT_THREE_TIAO;
                }
                return CT_ONE_LONG;
            }else{
                if ( value_qsort[2] - value_qsort[0] <= 4) {
                    return CT_SHUN_ZI;
                }
                if ( value_qsort_A[2] - value_qsort_A[0] <= 4) {
                    return CT_SHUN_ZI;
                }
            }
        }
            break;
        case 4:
        {
            if( color_qsort[0] == color_qsort[1] && color_qsort[1] == color_qsort[2]  && color_qsort[2] == color_qsort[3] ){
                if ( value_qsort[3] - value_qsort[0] <= 4 && !(value_qsort[0] == value_qsort[1] || value_qsort[1] == value_qsort[2] || value_qsort[2] == value_qsort[3])) {
                    return CT_TONG_HUA_SHUN;
                }
                if ( value_qsort_A[3] - value_qsort_A[0] <= 4 && !(value_qsort_A[0] == value_qsort_A[1] || value_qsort_A[1] == value_qsort_A[2] || value_qsort_A[2] == value_qsort_A[3])) {
                    return CT_TONG_HUA_SHUN;
                }
                return CT_TONG_HUA;
            }else if ( value_qsort[0] == value_qsort[1] || value_qsort[1] == value_qsort[2] || value_qsort[2] == value_qsort[3]) {
                if ( (value_qsort[0] == value_qsort[1] && value_qsort[1] == value_qsort[2]) || (value_qsort[1] == value_qsort[2] && value_qsort[2] == value_qsort[3]) ) {
                    return CT_THREE_TIAO;
                }else if (  value_qsort[0] == value_qsort[1] && value_qsort[2] == value_qsort[3] ){
                    return CT_TWO_LONG;
                }else{
                    return CT_ONE_LONG;
                }
            }else{
                if ( value_qsort[3] - value_qsort[0] <= 4 ) {
                    return CT_SHUN_ZI;
                }
                if ( value_qsort_A[3] - value_qsort_A[0] <= 4 ) {
                    return CT_SHUN_ZI;
                }
            }
        }
            break;
        default:
        {
            return cardTypeEx_Evaluation(cbCardData_tag, cbCardCount);
        }
            break;
    }
    return CT_EMPTY;
}