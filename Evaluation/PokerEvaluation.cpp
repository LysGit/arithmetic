//
//  PokerEvaluation.cpp
//  TestCpp
//
//  Created by 罗耀生 on 14-6-21.
//
//

#include "PokerEvaluation.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>


//0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,	//方块 A - K
//0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,0x1C,0x1D,	//梅花 A - K
//0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,	//红桃 A - K
//0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,	//黑桃 A - K


//数值掩码
#define	LOGIC_MASK_COLOR			0xF0								//花色掩码
#define	LOGIC_MASK_VALUE			0x0F								//数值掩码

int cmp( const void *a , const void *b )
{
    return *(unsigned char *)a - *(unsigned char *)b;
}

void PokerEvaluation::sortCardList_Evaluation(unsigned char cbCardData[], unsigned char cbCardCount)
{
    qsort( cbCardData, cbCardCount, sizeof( cbCardData[0] ), cmp);
}

unsigned char PokerEvaluation::cardValue_Evaluation(unsigned char cbCardData)
{
    return cbCardData&LOGIC_MASK_VALUE;
}

unsigned char PokerEvaluation::cardColor_Evaluation(unsigned char cbCardData)
{
    return cbCardData&LOGIC_MASK_COLOR;
}

unsigned char PokerEvaluation::cardLogicValue_Evaluation(unsigned char cbCardData)
{
	unsigned char bCardValue = cardValue_Evaluation(cbCardData);
	return (bCardValue==1)?(bCardValue+13):bCardValue;
}

void PokerEvaluation::ptf_poker_Evaluation(unsigned char card)
{
    unsigned char color = cardColor_Evaluation( card );
    unsigned char value = cardLogicValue_Evaluation( card );
    switch ( color ) {
        case 0:
            printf(" ♦️");
            break;
        case 1:
            printf(" ♣️");
            break;
        case 2:
            printf(" ♥️");
            break;
        default:
            printf(" ♠️");
            break;
    }
    
    if ( value < 11) {
        printf("%d ", value);
    }else{
        switch ( value ) {
            case 11:
                printf("J ");
                break;
            case 12:
                printf("Q ");
                break;
            case 13:
                printf("K ");
                break;
            default:
                printf("A ");
                break;
        }
    }
}
