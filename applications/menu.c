/*
 * @Author: jiang chenhui
 * @Date: 2020-02-04 11:16:35
 * @LastEditTime : 2020-02-04 13:35:18
 * @LastEditors  : Please set LastEditors
 * @Description: oled menu
 * @FilePath: \stm32f407-rushb\applications\menu.c
 */
#include "menu.h"

KEY_MSG keymsg = {KEY_NULL, KEY_OFF};

rt_uint8_t STEP = 10;

void Menu_Null(void);

rt_uint16_t Line_KP;
rt_uint16_t Line_KD;
rt_uint16_t Left_KP;
rt_uint16_t Left_KD;
rt_uint16_t Right_KP;
rt_uint16_t Right_KD;
rt_uint16_t BASE_SPEED;

//一级菜单
MENU_PRMT MainMenu_Prmt;

MENU_TABLE MainMenu_Table[] =
    {
        {"1.ReadFlash", Menu_Null, NULL},

        {"2.MotorDebug", Menu_motor, NULL},

};

// 二级菜单 电机参数
MENU_PRMT Motro_Prmt;

MENU_TABLE Motro_MenuTable[] =
    {
        {"1.Line_KP    ", Menu_Null, (rt_uint16_t *)&Line_KP},
        {"2.Line_KD    ", Menu_Null, (rt_uint16_t *)&Line_KD},

        {"3.Left_KP    ", Menu_Null, (rt_uint16_t *)&Left_KP},
        {"4.Left_KD    ", Menu_Null, (rt_uint16_t *)&Left_KD},

        {"5.Right_KP   ", Menu_Null, (rt_uint16_t *)&Right_KP},
        {"6.Right_KD   ", Menu_Null, (rt_uint16_t *)&Right_KD},

        {"7.BASE_SPEED  ", Menu_Null, (rt_uint16_t *)&BASE_SPEED},
};

/******************************************************************************
*  @brief  按键参数调整通用函数
******************************************************************************/
void adjustParam(Site_t site, rt_uint16_t *param, rt_uint8_t max_param_bit)
{
    oled_show_mode = 0;
    OLED_ShowNum(site.x, site.y, (rt_uint32_t)(*param), max_param_bit);

    do
    {
        wait_KEY();

        switch (keymsg.key)
        {
        case (KEY_U):
            (*param)++;
            OLED_ShowNum(site.x, site.y, (rt_uint32_t)(*param), max_param_bit);
            break;

        case (KEY_D):
            if (*param > 0)
                (*param)--;

            OLED_ShowNum(site.x, site.y, (rt_uint32_t)(*param), max_param_bit);
            break;

        case (KEY_L):
            if (*param >= STEP)
                (*param) -= STEP;

            OLED_ShowNum(site.x, site.y, (rt_uint32_t)(*param), max_param_bit);
            break;

        case (KEY_R):
            (*param) += STEP;
            OLED_ShowNum(site.x, site.y, (rt_uint32_t)(*param), max_param_bit);
            break;

        default:
            break;
        }

        if (*param <= 0)
            *param = 0;
    } while (keymsg.key != KEY_B);

    oled_show_mode = 1;
}

void Menu_Null()
{
    //Delay_ms(100);
}

/******************************************************************************
* FunctionName   : Menu_PrmtInit()
* Description    : 初始化菜单参数
* EntryParameter : prmt - 菜单参数, num -每页显示项数, page - 最大显示页数
* ReturnValue    : None
*******************************************************************************/
void Menu_PrmtInit(MENU_PRMT *prmt, rt_uint8_t num, rt_uint8_t page)
{
    prmt->ExitMark = 0; //清除退出菜单标志

    prmt->Cursor = 0;    //光标清零
    prmt->PageNo = 0;    //页
    prmt->Index = 0;     //索引
    prmt->DispNum = num; //页最多显示项数

    prmt->MaxPage = page; //最多页数
}

/******************************************************************************
* FunctionName   : wait_KEY()
* Description    : ????
* EntryParameter : None
* ReturnValue    : ???
*******************************************************************************/
KEY_e wait_KEY(void)
{
    while (keymsg.status == KEY_OFF)
        ; //等待按键按下

    keymsg.status = KEY_OFF;

    bb();

    return keymsg.key;
}

/******************************************************************************
* FunctionName   : Menu_Display()
* Description    : 显示菜单
* EntryParameter : page - 显示页,dispNum - 每一页显示项,cursor - 光标位置
* ReturnValue    : None
*******************************************************************************/
void Menu_Display(MENU_TABLE *menuTable, rt_uint8_t pageNo, rt_uint8_t dispNum, rt_uint8_t cursor)
{
    rt_uint8_t i;

    for (i = 0; i < dispNum; i++)
    {
        if (cursor == i)
        {
            /*反白显示当前光标选中项*/
            oled_show_mode = 0;
            OLED_ShowString(0, (i + 1), menuTable[pageNo + i].MenuName);
            oled_show_mode = 1;

            /*若此菜单有需要调的参数，则显示该参数*/
            if (menuTable[pageNo + i].DebugParam != NULL)
            {
                rt_uint32_t num_t = (*(menuTable[pageNo + i].DebugParam));
                //oled_show_mode = 0;
                OLED_ShowNum(90, i + 1, num_t, 4);
                //oled_show_mode = 1;
            }
        }
        else
        {
            /*正常显示其余菜单项*/
            OLED_ShowString(0, (i + 1), menuTable[pageNo + i].MenuName);

            /*若此菜单有需要调的参数，则显示该参数*/
            if (menuTable[pageNo + i].DebugParam != NULL)
            {
                rt_uint32_t num_t = (*(menuTable[pageNo + i].DebugParam));

                //oled_show_mode = 0;
                OLED_ShowNum(90, i + 1, num_t, 4);
                //oled_show_mode = 1;
            }
        }
    }
}

/******************************************************************************
* FunctionName   : Menu_Move()
* Description    : 菜单移动
* EntryParameter :  prmt - 菜单参数, key -按键值
* ReturnValue    : 有确认返回0,无确认返回1
******************************************************************************/
rt_uint8_t Menu_Move(MENU_PRMT *prmt, KEY_e key)
{
    rt_uint8_t rValue = 1;

    switch (key)
    {
    case KEY_U:
        if (prmt->Cursor != 0) // 光标不在顶端
            prmt->Cursor--;    // 光标上移
        else                   // 光标在顶端
        {
            if (prmt->PageNo != 0) // 页面没有到最小
                prmt->PageNo--;    // 向上翻页
            else
            {
                //这个难道是从最开始向上就到了最后一项
                prmt->Cursor = prmt->DispNum - 1; // 光标到底
                prmt->PageNo = prmt->MaxPage - 1; // 页数减1
            }
        }

        break;

    case KEY_D:
        if (prmt->Cursor < prmt->DispNum - 1) // 光标没有到底，移动光标
            prmt->Cursor++;
        else //光标到底
        {
            if (prmt->PageNo < prmt->MaxPage - 1) // 页面没有到底，页面移动
                prmt->PageNo++;                   // 翻页
            else                                  // 页面和光标都到底，返回开始页
            {
                prmt->Cursor = 0;
                prmt->PageNo = 0;
            }
        }

        break;

    case KEY_B:                                    // 确认
        prmt->Index = prmt->Cursor + prmt->PageNo; //计算执行项的索引
        rValue = 0;
        break;

    case KEY_L: // 左键返回上级菜单
        //prmt->Cursor = 0;
        //prmt->PageNo = 0;
        prmt->ExitMark = 1;

        break;

    case KEY_R:                           // 右键跳到底部
        prmt->Cursor = prmt->DispNum - 1; // 光标到底
        prmt->PageNo = prmt->MaxPage - 1; // 最后页

        break;

    default:
        break;
    }

    return rValue; // 返回执行索引
}

/******************************************************************************
* FunctionName   : Menu_Process()
* Description    : 处理菜单项
* EntryParameter : menuName - 菜单名称,prmt - 菜单参数,table - 菜单表项, num -菜单项数
* ReturnValue    : None
******************************************************************************/
void Menu_Process(rt_uint8_t *menuName, MENU_PRMT *prmt, MENU_TABLE *table, rt_uint8_t num)
{
    KEY_e key;
    Site_t site;
    rt_uint8_t page; //显示菜单的页数

    if (num - PAGE_DISP_NUM <= 0)
        page = 1;
    else
    {
        page = num - PAGE_DISP_NUM + 1;
        num = PAGE_DISP_NUM;
    }

    // 显示项数和页数的设置
    Menu_PrmtInit(prmt, num, page);

    do
    {
        OLED_ShowString(0, 0, menuName); //显示菜单标题

        // 显示菜单项
        Menu_Display(table, prmt->PageNo, prmt->DispNum, prmt->Cursor);

        key = wait_KEY();
        //key = Key_Scan();                       // 获取按键

        if (Menu_Move(prmt, key) == 0) // 菜单移动，按下确认键
        {
            // 判断此菜单项有无需要调节的参数，有则进入参数调节
            if (table[prmt->Index].DebugParam != NULL && table[prmt->Index].ItemHook == Menu_Null)
            {
                OLED_ShowNum(90, (1 + prmt->Cursor), *(table[prmt->Index].DebugParam), 4);

                site.x = 90;
                site.y = 1 + prmt->Cursor;
                adjustParam(site, table[prmt->Index].DebugParam, 4);
            }
            // 不是参数调节就执行菜单函数
            else
            {
                table[prmt->Index].ItemHook();
            }
        }
    } while (prmt->ExitMark == 0);

    OLED_Clear();
    Delay_ms(50);
}

void read_data_from_flash(void)
{
    // STMFLASH_Read(FLASH_SAVE_ADDR, (rt_uint32_t *)save_data, save_SIZE);

    // Line_KP = save_data[0];
    // Line_KD = save_data[1];

    // Left_KP = save_data[2];
    // Left_KD = save_data[3];

    // Right_KP = save_data[4];
    // Right_KD = save_data[5]; ////////////////////////////////////////////////////////////

    // BASE_SPEED = save_data[6];
}

void save_data_to_flash(void)
{
    // save_data[0] = Line_KP;
    // save_data[1] = Line_KD;

    // save_data[2] = Left_KP;
    // save_data[3] = Left_KD;

    // save_data[4] = Right_KP;
    // save_data[5] = Right_KD; ////////////////////////////////////////////////////

    // save_data[6] = BASE_SPEED;

    // STMFLASH_Write(FLASH_SAVE_ADDR, (rt_uint32_t *)save_data, save_SIZE);
}

/******************************************************************************
* FunctionName   : MainMenu_Set()
* Description    : 常规设置
* EntryParameter : None
* ReturnValue    : None
*******************************************************************************/
void MainMenu_Set(void)
{
    OLED_Clear();
    read_data_from_flash();

    //	rt_uint8_t menuNum = sizeof(MainMenu_Table) / sizeof(MainMenu_Table[0]);    // 菜单项数
    //    Menu_Process(" -= Setting =- ", &MainMenu_Prmt, MainMenu_Table, menuNum);
    Menu_motor();

    save_data_to_flash(); //菜单退出，保存参数
    OLED_Clear();
}

/******************************************************************************
* FunctionName   : Menu_motor()
* Description    : 电机设置
* EntryParameter : None
* ReturnValue    : None
*******************************************************************************/
void Menu_motor(void)
{
    rt_uint8_t menuNum;
    OLED_Clear();

    menuNum = sizeof(Motro_MenuTable) / sizeof(Motro_MenuTable[0]); // 菜单项数

    Menu_Process("-= MotorDebug =-", &Motro_Prmt, Motro_MenuTable, menuNum);
}

/// 不精确的延时
static void Key_Delay(__IO rt_uint32_t nCount)
{
    for (; nCount != 0; nCount--);
}

rt_uint8_t Key_Scan(GPIO_TypeDef *GPIOx, rt_uint16_t GPIO_Pin)
{
    // Key_Delay(60000); //
    // //检测是否有按键按下
    // if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON)
    // {
    //     //延时消抖
    //     Key_Delay(60000);

    //     if (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON)
    //     {
    //         //等待按键释放
    //         while (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_ON)
    //             ;

    //         return KEY_ON;
    //     }
    //     else
    //         return KEY_OFF;
    // }
    // else
    //     return KEY_OFF;
}