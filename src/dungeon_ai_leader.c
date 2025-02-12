#include "global.h"
#include "dungeon_ai_leader.h"

#include "constants/dungeon.h"
#include "constants/item.h"
#include "constants/iq_skill.h"
#include "constants/move_id.h"
#include "constants/status.h"
#include "constants/targeting.h"
#include "constants/dungeon_action.h"
#include "code_80521D0.h"
#include "dungeon_ai_targeting.h"
#include "dungeon_items.h"
#include "dungeon_leader.h"
#include "dungeon_visibility.h"
#include "dungeon_util.h"
#include "dungeon_capabilities.h"
#include "dungeon_pokemon_attributes.h"
#include "dungeon_movement.h"
#include "charge_move.h"
#include "pokemon.h"
#include "pokemon_3.h"
#include "code_8077274_1.h"

extern u8 gUnknown_202F221;
extern u8 gUnknown_202F222;
extern u8 gUnknown_202F32C;
extern u8 gUnknown_202F32D;
extern u8 gUnknown_203B434;
extern u8 gAvailablePokemonNames[];

extern u8 *gUnknown_80FA5B4[];
extern u8 *gUnknown_80FE478[];
extern u8 *gUnknown_80FD2CC[];
extern u8 gUnknown_80F58F4[NUM_DUNGEON_ACTIONS][2];
extern u8 *gUnknown_80FE6D4[];

void sub_8075BA4(Entity *param_1, u8 param_2);
void sub_804178C(u8 param_1);
void nullsub_95(Entity *);
bool8 IsNotAttacking(Entity *, bool8);
extern void sub_80671A0(Entity *);
extern void sub_8067110(Entity *);
void sub_807CABC(Entity *target);
void sub_8041888(u8 param_1);
void sub_8085140(void);
void sub_807360C(void);
void sub_805EFB4(Entity *, u8);
void sub_8074FB0(Entity *, u8, Position *);
extern void SetMessageArgument(u8 *buffer, Entity *r1, u32);

void sub_8066D04(Entity *);
void sub_8066744(Entity *);
void sub_8066E14(Entity * );
void sub_807348C(void);
void sub_80732F0(void);
void sub_807FD84(Entity *);
void sub_8066BD4(Entity*);
void sub_8067510(Entity *);
void sub_8067884(Entity *);
void sub_804267C(void);
void sub_807CB3C(Entity *);
void sub_8067904(Entity *, u32);
void sub_80668D0(Entity *);
void sub_8066AC0(Entity *);
void sub_8066CF0(Entity *);
void sub_8066FA4(Entity *);
void sub_806675C(Entity *,bool8);
void sub_806684C(Entity *,bool8);
void sub_807FE9C(Entity *,Position *,u32,u32);
extern u8 sub_8044B28(void);
extern u8 UseAttack(Entity *);
void sub_8052740(u32);
void sub_806A1E8(Entity *pokemon);
extern void sub_803E46C(u32);
extern void sub_80694C0(Entity *, s32, s32, u32);
bool8 sub_804AE08(Position *pos);
void sub_8073D08(Entity *pokemon);
void sub_8073CFC(Entity *pokemon);
void sub_8073CF0(Entity *pokemon);
bool8 sub_8044B84(void);
void sub_8046D20(void);
extern void sub_8074094(Entity *);
extern void sub_8071DA4(Entity *);
extern void sub_807D148(Entity *pokemon, Entity *r1, u32 r2, Position *r3);
u32 sub_8075818(Entity *entity);

bool8 TargetLeader(Entity *pokemon)
{
    if (pokemon->info->isNotTeamMember)
    {
        return FALSE;
    }
    return TacticsTargetLeader(pokemon->info->tactic);
}

Entity* GetLeaderIfVisible(Entity *pokemon)
{
    if (!pokemon->info->isNotTeamMember)
    {
        Entity *leader = GetLeader();
        if (leader &&
            leader->info->waitingStatus != STATUS_DECOY &&
            CanTarget(pokemon, leader, FALSE, FALSE) == TARGET_CAPABILITY_CANNOT_ATTACK &&
            CanTargetEntity(pokemon, leader))
        {
            return leader;
        }
    }
    return NULL;
}

bool8 sub_8072CF4(Entity *entity)
{
    bool8 bVar4;
    bool8 bVar5;
    Move *move;
    s32 index;
    EntityInfo *info;
    bool8 bVar14;
    Position PStack_24;
    Position pos1;

    sub_804178C(1);
    gUnknown_203B434 = 1;
    info = entity->info;
    info->useHeldItem = FALSE;
    info->fillF3 = 0;
    gDungeon->unkB8 = entity;
    if (gUnknown_80F58F4[(info->action).action][0] != 0) {
        if (info->isTeamLeader) {
            sub_805EFB4(entity,gUnknown_80F58F4[(info->action).action][1]);
        }
        else {
            sub_8075BA4(entity,gUnknown_80F58F4[(info->action).action][1]);
        }
    }
    if ((CannotAttack(entity, FALSE)) && (IsCharging(entity, TRUE))) {
        sub_8079764(entity);
    }

    for(index = 0; index < MAX_MON_MOVES; index++)
    {
        move = &info->moves[index];
        if ((move->moveFlags & MOVE_FLAG_EXISTS)) {
            move->moveFlags2 &= ~(MOVE_FLAG2_UNK4);
        }
    }
    if (!IsNotAttacking(entity, FALSE)) {
        if (UseAttack(entity)) {
            if (sub_8044B28()) {
                return FALSE;
            }
            if (!EntityExists(entity)) {
                return FALSE;
            }
            if (gUnknown_202F32D != 0) {
                return TRUE;
            }
        }
        if (!info->isTeamLeader) {
            sub_8052740(10);
        }
        sub_806A1E8(entity);
        sub_803E46C(10);
    }
    if (((ACTION_PASS_TURN < info->action.action) && (info->action.action != 4)) && (info->action.action != ACTION_WALK)) {
        info->attacking = TRUE;
    }
    bVar14 = FALSE;
    info->unk14A = 0;
    gUnknown_202F221 = 0;
    gUnknown_202F222 = 0;
    switch(info->action.action) {
        case ACTION_WALK:
            if(info->immobilizeStatus == STATUS_SHADOW_HOLD)
            {
                goto _282;  
            }
            else if(info->immobilizeStatus == STATUS_CONSTRICTION)
            {
                goto _282;  
            }
            else if(info->immobilizeStatus == STATUS_INGRAIN)
            {
                goto _282;  
            }
            else if(info->immobilizeStatus == STATUS_WRAP)
            {
                goto _282;  
            }
            else if(info->immobilizeStatus == STATUS_WRAPPED)
            {
            _282:
                info->action.action = ACTION_NOTHING;
                info->waiting = TRUE;
            }
            else {
                bVar5 = FALSE;
                pos1.x = (entity->pos).x + gAdjacentTileOffsets[(info->action).direction].x;
                pos1.y = (entity->pos).y + gAdjacentTileOffsets[(info->action).direction].y;
                if ((!(info->flags & MOVEMENT_FLAG_SWAPPING_PLACES_PETRIFIED_ALLY)) &&
                    (!CanMoveInDirection(entity,(info->action).direction))) {
                    bVar5 = TRUE;
                }
                if (bVar5) {
                    info->action.action = ACTION_NOTHING;
                    info->waiting = TRUE;
                    break;
                }
                else
                {
                    PStack_24.x = entity->pos.x;
                    PStack_24.y = entity->pos.y;
                    sub_80694C0(entity,pos1.x,pos1.y,0);
                    sub_8074FB0(entity,(info->action).direction,&PStack_24);
                    if (((IQSkillIsEnabled(entity, IQ_SUPER_MOBILE)) && (info->transformStatus != STATUS_MOBILE)) &&
                        (!HasHeldItem(entity,ITEM_MOBILE_SCARF))) {
                        sub_804AE08(&entity->pos);
                    }
                    bVar14 = TRUE;
                    break;
                }
            }
            break;
        case ACTION_USE_MOVE_AI:
            sub_807CABC(entity);
            break;
        case ACTION_STAIRS:
            if ((gDungeon->dungeonLocation.id == DUNGEON_METEOR_CAVE) && (!gDungeon->deoxysDefeat)) {
                SendMessage(entity,*gUnknown_80FA5B4); // It's impossible to go down the stairs now!
            }
            else
            {
                sub_804267C();
                gDungeon->unk2 = 1;
                gUnknown_202F32C = (info->action).direction;
            }
            break;
        case ACTION_EAT_BERRY_SEED_DRINK:
        case 0xe:
        case ACTION_USE_TM:
            sub_8067110(entity);
            break;
        case ACTION_USE_ORB:
            sub_807CB3C(entity);
            break;
        case ACTION_PICK_UP_PLAYER:
            sub_8066744(entity);
            break;
        case ACTION_GIVE_ITEM:
            sub_80668D0(entity);
            break;
        case ACTION_TAKE_ITEM:
            sub_8066AC0(entity);
            break;
        case 0x3e:
            sub_8066BD4(entity); // ITEM_SWITCH_TOOLBOX (When you switch item in Toolbox)
            break;
        case ACTION_USE_ITEM:
            sub_8066CF0(entity);
            break;
        case ACTION_SET_ITEM:
            sub_806675C(entity, TRUE);
            break;
        case ACTION_UNSET_ITEM:
            sub_806684C(entity, TRUE);
            break;
        case 0x3b:
            gDungeon->unkBC = gDungeon->teamPokemon[(info->action).unk4[0].actionUseIndex];
            break;
        case ACTION_PLACE_ITEM:
            sub_8066D04(entity);
            break;
        case 10: // Switch with Item on Ground
            sub_8066E14(entity);
            break;
        case 0x3a: // Switch with Item on Ground (also??)
            sub_8066FA4(entity);
            break;
        case ACTION_THROW_ITEM_PLAYER:
        case ACTION_THROW_STRAIGHT_PLAYER:
        case ACTION_THROW_ARC_PLAYER:
            if (ToolboxEnabled(info)) {
                nullsub_95(entity);
                sub_80671A0(entity);
                break;
            }
            SetMessageArgument(gAvailablePokemonNames,entity,0);
            SendMessage(entity,*gUnknown_80FE6D4);
            break;
        case ACTION_TALK_FIELD:
            sub_8067510(entity);
            break;
        case ACTION_USE_MOVE_PLAYER:
            sub_8067884(entity);
            break;
        case ACTION_STRUGGLE:
            sub_8067904(entity, MOVE_STRUGGLE);
            break;    
        case ACTION_REGULAR_ATTACK:
            sub_8067904(entity, MOVE_REGULAR_ATTACK);
            break;
        case 0x25:
            sub_807FE9C(entity,&entity->pos,0,0);
            break;
        case ACTION_PICK_UP_AI:
            sub_8073D08(entity);
            break;
        case ACTION_EAT_AI:
            sub_8073CF0(entity);
            break;
        case ACTION_THROW_ITEM_AI:
            sub_8073CFC(entity);
            break;  
        case ACTION_SECOND_THOUGHTS:
            SetMessageArgument(gAvailablePokemonNames,entity,0);
            SendMessage(entity,*gUnknown_80FE478);
            break;
        default:
            info->action.action = ACTION_PASS_TURN;
            break;
    }
    sub_807FD84(entity);
    if (EntityExists(entity)) {
        if (entity->info->unk14A == 0) {
            entity->info->unk14A = 0;
            sub_8079764(entity);
        }
        sub_8041888(0);
        if (EntityExists(entity)) {
            sub_8085140();
            if (info->unk14B != 0) {
                bVar4 = FALSE;
                info->unk14B = 0;

                for(index = 0; index < MAX_MON_MOVES; index++)
                {
                    move = &info->moves[index];
                    if ((info->moves[index].moveFlags & MOVE_FLAG_EXISTS) && (move->moveFlags & MOVE_FLAG_LAST_USED)) {
                        move->PP = 0;
                        bVar4 = TRUE;
                    }
                }
                if (bVar4) {
                    SendMessage(entity,*gUnknown_80FD2CC);
                }
            }
            sub_807360C();
            if (!sub_8044B84()) {
                sub_807348C();
                sub_80732F0();
                if (!EntityExists(entity)) {
                    return FALSE;
                }
            }
            if (bVar14) {
                sub_8075818(entity);
            }
            if (EntityExists(entity)) {
                if (!sub_8044B84()) {
                    sub_8046D20();
                }
                sub_8041888(0);
                if (((EntityExists(entity)) && (!info->aiNextToTarget)) && (!bVar14)) {
                    if (sub_80706A4(entity,&entity->pos) != '\0') {
                        sub_807D148(entity,entity,0,0);
                    }
                    sub_8074094(entity);
                    sub_8071DA4(entity);
                }
            }
        }
    }
    return FALSE;
}
