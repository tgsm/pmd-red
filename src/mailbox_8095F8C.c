#include "global.h"
#include "code_80958E8.h"
#include "mailbox_8095F8C.h"

extern unkStruct_203B490 *gUnknown_203B490;

s32 CountFilledMailboxSlots(void)
{
    s32 index;
    s32 counter;

    counter = 0;
    for(index = 0; index < NUM_MAILBOX_SLOTS; index++)
    {
        if(!IsMailSlotEmpty(index))
            counter++;
    }
    return counter;
}

UNUSED static bool8 sub_8095FB0(WonderMail *mail)
{
    s32 index;

    for(index = 0; index < NUM_MAILBOX_SLOTS; index++)
    {
        if(gUnknown_203B490->mailboxSlots[index].mailType == MAIL_TYPE_NONE)
        {
            gUnknown_203B490->mailboxSlots[index] = *mail;
            return FALSE;
        }
    }
    return TRUE;
}

WonderMail *GetMailboxSlotInfo(u8 index)
{
    return &gUnknown_203B490->mailboxSlots[index];
}

bool8 IsMailSlotEmpty(u8 index)
{
    if(gUnknown_203B490->mailboxSlots[index].mailType == MAIL_TYPE_NONE)
        return TRUE;
    else
        return FALSE;
}

void ResetMailbox(void)
{
    s32 index;
    for(index = 0; index < NUM_MAILBOX_SLOTS; index++)
    {
        ResetMailboxSlot(index);
    }
}

void ResetMailboxSlot(u8 index)
{
    gUnknown_203B490->mailboxSlots[index].mailType = MAIL_TYPE_NONE;
    gUnknown_203B490->mailboxSlots[index].unk4.dungeon.id = 99;
    gUnknown_203B490->mailboxSlots[index].unk4.dungeon.floor = 0;
    gUnknown_203B490->mailboxSlots[index].rewardType = MONEY1;
}
