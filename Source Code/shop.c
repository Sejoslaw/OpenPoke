//======================================================================
//
//	OpenPoké shopping system
//
//	(comments, kudos, flames to "foo@helmetedrodent.kickassgamers.com")
//
//======================================================================
#include "openpoke.h"

extern void RepairMap();

extern const unsigned long* itemicons[];
extern const unsigned short shopPal[16];
extern const unsigned short shopTiles[528];
extern const unsigned short shopMap[640];

void Store_WriteList(u16* inv, int scrolloffset, int cursor)
{
	int idx,i=0;
	char blub[32];

	vwBlackTransparentLUT();
	for(idx = 0; idx < 6; idx++)
	{
		if(inv[idx+scrolloffset])
		{
			if(items[inv[idx+scrolloffset]].price > MyPlayer.cash)
			{
				vwf_set_color(TEXT_INK, 3);
				vwf_set_color(TEXT_SHADOW, 1);
			} else
			{
				vwf_set_color(TEXT_INK, 2);
				vwf_set_color(TEXT_SHADOW, 3);
			}
			vwWrite(128+8,(idx+3)*16,"                            ");
			vwWrite(128+8,(idx+3)*16,items[inv[idx+scrolloffset]].name);

			vw_SetSmall();
			sprintf(blub,"$%4d ", items[inv[idx+scrolloffset]].price);
			vwWrite(224,(idx+3)*16,(char*)blub);
			vw_SetBig();
		}
		else
		{
			vwf_set_color(TEXT_INK, 2);
			vwf_set_color(TEXT_SHADOW, 3);
			vwWrite(128+8,(idx+3)*16,"                            ");
			if(i==0) vwWrite(128+8,(idx+3)*16,strShopBack);
			i++;
		}
	}
}

void Store_ShowItem(int index)
{
	int itempicbuf[0x120];

	CpuFastClear(0, vwDestination, 0x1800); \
	vwWhiteTransparentLUT();
	if(index==0)
		vwWrite(0,3,strShopBack);
	else
		vwWrite(0,3,(char*)items[index].description);
	vwBlackTransparentLUT();

	DmaCopy(itemicons[(index*2)+1], MEM_PAL_OBJ + 0xA0, 32);

	LZ77UnCompWram((u8*)itemicons[index*2], itempicbuf);
	DmaCopy(itempicbuf, MEM_VRAM_OBJ+0x6000, 0x60);
	DmaCopy(itempicbuf + 0x18, MEM_VRAM_OBJ+0x6000 + 0x80, 0x60);
	DmaCopy(itempicbuf + 0x30, MEM_VRAM_OBJ+0x6000 + 0x100, 0x60);
}

void Store_DrawBackdrop()
{
	//TODO: Detect player's orientation and draw accordingly

	extern u8	gMapOfsX, gMapOfsY;
	int ix, iy;
	DmaClear(0, MEM_VRAM+0xE000, 0x1800);

	gMapOfsX = 0;
	gMapOfsY = 0;
	for(iy=1; iy<7; iy++)
		for(ix=0; ix<5; ix++)
			mapDrawMeta(ix, iy, mhGetMetaTile(currentMapHeader, ix, iy));

	CpuFastCopy(Sprites[Actors[0].sprite].spriteStart + 0x80, (u16*)MEM_VRAM_OBJ, 0x100);
	CpuFastCopy(Sprites[Actors[1].sprite].spriteStart, (u16*)MEM_VRAM_OBJ+0x100, 0x100);
	OamBak[0].HPos = 32;
	OamBak[0].VPos = 64;
	OamBak[1].HPos = 32;
	OamBak[1].VPos = 32;


	DmaArrayCopy(shopTiles, MEM_VRAM + 0x0000);
	DmaArrayCopy(shopPal, MEM_PAL_BG + 0x01A0);

	for(ix=0;ix<640;ix++)
		if(shopMap[ix+1]) //skip null tiles
			BG1MAP[ix] = shopMap[ix+1] | 0xD000;

}

void Store_DrawUI(int cursor)
{
	int i;
	char buffy[32];

	CleanUpBG0();
	REG_BG0HOFS= 0;	REG_BG0VOFS= 0;
	REG_BG1HOFS= 0;	REG_BG1VOFS= 0;
	REG_BG2HOFS= 0;	REG_BG2VOFS= 0;
	REG_BG3HOFS= 0;	REG_BG3VOFS= 0;

	vwBlackTransparentLUT();
	for(i=0; i<6; i++)
		vwSetLine(12,16,(i<<1)+1,304+(64*i),15);
	vwWrite(128,(cursor+3)*16,strArrow);
	vwSetLine(5,24,14,96,15);
	vwSetLine(5,24,16,160,15);
	vwSetLine(5,24,18,224,15);
	vwWrite(4,102,strShopMoney);
	sprintf(buffy,"$%4d ",MyPlayer.cash);
	vw_SetSmall();
	vwWrite(32,116,buffy);
	vw_SetBig();
	vwSetLine(1,8,1,512,15);
	vwSetLine(1,8,2,544,15);

	OamBak[120].CharNo = 768;
	OamBak[120].Pltt = 5;
	OamBak[120].HPos = 8;
	OamBak[120].VPos = 124;
	OamBak[120].Shape = 0;
	OamBak[120].Size = 2;
	OamBak[120].Priority = 0;
}

void Store_WriteWantedCt(u16* inv, int wantedct, int cursor)
{
	char buffy[32];
	vwClearLine(1,36);
	vw_SetSmall();
	sprintf(buffy, "%2d", wantedct);
	vwWrite(4,145,buffy);
	sprintf(buffy, "$%d", items[inv[cursor]].price * wantedct);
	vwWrite(62,145,buffy);
	vw_SetBig();
}
void Store_WriteSellingCt(int price, int wantedct)
{
	char buffy[32];
	vwClearLine(1,36);
	vw_SetSmall();
	sprintf(buffy, "%2d", wantedct);
	vwWrite(4,145,buffy);
	sprintf(buffy, "$%d", price * wantedct);
	vwWrite(62,145,buffy);
	vw_SetBig();
}

void Store_Buy(u16* inv)
{
	int cursor = 0;
	int scrolloffset = 0;
	int wantedct;

	int i = 0;

	vwClear(0);

	//We impose a 128 item limit here to minimize damage from unterminated inventories.
	AGBPrintf("DoStore: determining inventory size...\n");
	while(inv[i] && i < 128) i++;

	Store_WriteList(inv, scrolloffset, cursor);
	Store_ShowItem(inv[scrolloffset+cursor]);
	Store_DrawUI(cursor);
	Store_DrawBackdrop();

	FadeIn();

	while(1)
	{
		DoVBlank();
		KeyRead();

		if(Trg & B_BUTTON) break;

		if(Trg & A_BUTTON)
		{
			if(inv[scrolloffset+cursor] == 0) break;

			OamBak[120].Priority = 3;
			if(items[inv[cursor+scrolloffset]].price > MyPlayer.cash)
			{
				sayf(SPEECH, strShopNotEnoughMoney);
			} else
			{
				sayf(SPEECH,strShopCertainly, items[inv[cursor+scrolloffset]].name);

				wantedct = 1;
				DrawFrame(16, 14, 10, 4);
				Store_WriteWantedCt(inv, wantedct,cursor+scrolloffset);
				vwSetLine(17,12,11,672,15);
				while(1)
				{
					DoVBlank();
					KeyRead();
					if(Trg & B_BUTTON)
					{
						wantedct = 0;
						break;
					}
					if(Trg & A_BUTTON) break;
					if(Trg & U_KEY)
					{
						if(items[inv[cursor+scrolloffset]].price * wantedct >= MyPlayer.cash)
						{
							//ignore or wrap? LET'S ROCK!
						} else
						{
							wantedct++;
							Store_WriteWantedCt(inv, wantedct,cursor+scrolloffset);
						}
					}
					if(Trg & D_KEY)
					{
						if(wantedct == 1)
						{
							//ignore or wrap? LET'S ROCK!
						} else
						{
							wantedct--;
							Store_WriteWantedCt(inv, wantedct,cursor+scrolloffset);
						}
					}
				}
				if(wantedct)
				{
					Store_DrawUI(cursor);
					OamBak[120].Priority = 3;

					sayf(SPEECH,strShopConfirm, items[inv[cursor+scrolloffset]].name, wantedct, items[inv[cursor+scrolloffset]].price * wantedct);
					if(!SimpleYesNoLoop())
					{
						MyPlayer.cash -= items[inv[cursor+scrolloffset]].price * wantedct;
						while(wantedct--)
							GiveItem(inv[cursor+scrolloffset]);
						sayf(SPEECH,strShopThankYou);
					}
				}
			}
			Store_DrawUI(cursor);
			Store_DrawBackdrop();
			Store_WriteList(inv, scrolloffset, cursor);
			Store_ShowItem(inv[scrolloffset+cursor]);
		}

		if(Trg & U_KEY)
		{
			vwWrite(128,(cursor+3)*16,strArrowBlank);
			if(cursor==0)
			{
				if(scrolloffset > 0) scrolloffset--;
				Store_WriteList(inv, scrolloffset, cursor);
			} else
			{
				cursor--;
			}
			Store_ShowItem(inv[scrolloffset+cursor]);
			vwWrite(128,(cursor+3)*16,strArrow);
		} else if((Trg & D_KEY) && (inv[scrolloffset+cursor])) //can't pass Cancel.
		{
			vwWrite(128,(cursor+3)*16,strArrowBlank);
			if(cursor==5)
			{
				if(scrolloffset < 40) scrolloffset++;
				Store_WriteList(inv, scrolloffset, cursor);
			} else
			{
				cursor++;
			}
			Store_ShowItem(inv[scrolloffset+cursor]);
			vwWrite(128,(cursor+3)*16,strArrow);
		}
	}
}



extern anInventoryItem inventory[200] INEWRAM;

extern const unsigned short inventoryPal[16];
extern const unsigned short inventoryTiles[1056];
extern const unsigned short inventoryMap[640];

extern const unsigned long* itemicons[];

extern const unsigned short dannybagTiles[4096];
extern const unsigned short dannybagPal[16];


extern const anInventoryPage InventoryPages[6];

extern void Inventory_ShowItem(int index);
extern void Inventory_WriteList(int pageoffset, int scrolloffset, int cursor);
extern int Inventory_MultipleChoice(int left, int top, int width, int choices, int bcancel); //CHOICELIST choices);

void Store_Sell()
{
	int idx, page = 0;
	int cursor = 0;
	int scrolloffset = 0;
	int red=0;
	int thisitem, wantedct;
	char monies[32];

Redraw:
	if(red==0) REG_DISPCNT = 0;
	CleanUpCrap();
	ClearOamBak();
	DmaArrayCopy(inventoryTiles, MEM_VRAM + 0x0000);
	DmaArrayCopy(inventoryPal, MEM_PAL_BG + 0x0000);
	DmaArrayCopy(inventoryMap, MEM_VRAM + 0xE800);
	LoadFrame();

	Inventory_WriteList(InventoryPages[page].offset, scrolloffset, cursor);
	Inventory_ShowItem(inventory[InventoryPages[page].offset+scrolloffset+cursor].itemidx);
	for(idx=0; idx<6; idx++)
		vwSetLine(11,18,(idx<<1)+1,224+(64*idx),15);
	vwWrite(6,(cursor+2)*16,strArrow);

	vwWhiteTransparentLUT();
	//vwWrite(132,32,(char*)InventoryPages[page].name2);
	sprintf(monies,"$%4d",MyPlayer.cash);
	vwWrite(148,32,monies);
	vwSetLine(1,10,1,242,15);

	DmaArrayCopy(dannybagTiles, MEM_VRAM_OBJ + 0x0800);
	DmaArrayCopy(dannybagPal, MEM_PAL_OBJ + 0x0020);

	REG_BG1HOFS= 8;	REG_BG1VOFS= 0;
	REG_BG2HOFS= 0;	REG_BG2VOFS= 0;
	REG_BG3HOFS= 0;	REG_BG3VOFS= 0;

	OamBak[0].CharNo = 0;
	OamBak[0].Pltt = 0;
	OamBak[0].HPos = 8;
	OamBak[0].VPos = 124;
	OamBak[0].Shape = 0;
	OamBak[0].Size = 2;

	OamBak[1].HPos = 8;
	OamBak[1].VPos = 36;
	OamBak[1].CharNo = 64 + (page*64);
	OamBak[1].Pltt = 1;
	OamBak[1].Size = 3;
	OamBak[1].Shape = 0;

	if(red==0) { ResetDispCnt(); FadeIn(); }
	red = 1;

	while(1)
	{
		DoVBlank();
		KeyRead();

		if(Trg & A_BUTTON)
		{
			thisitem = InventoryPages[page].offset + scrolloffset + cursor;

			if(inventory[thisitem].itemidx == 0) break; //cancel
			vwNormalLUT();
			OamBak[0].Priority = 3;
			if(items[inventory[thisitem].itemidx].price)
			{
				if(inventory[thisitem].itemcnt > 1)
				{
					sayf(SPEECH, "%s?\nHow many would you like to sell?\1", items[inventory[thisitem].itemidx].name);
					wantedct = 1;
					DrawFrame(16, 14, 10, 4);
					Store_WriteSellingCt(items[inventory[thisitem].itemidx].price, wantedct);
					vwSetLine(17,12,11,672,15);
					while(1)
					{
						DoVBlank();
						KeyRead();
						if(Trg & B_BUTTON)
						{
							wantedct = 0;
							break;
						}
						if(Trg & A_BUTTON) break;
						if(Trg & U_KEY)
						{
							if(wantedct > inventory[thisitem].itemcnt)
							{
								wantedct=0;
							} else
							{
								wantedct++;
								Store_WriteSellingCt(items[inventory[thisitem].itemidx].price, wantedct);
							}
						}
						if(Trg & D_KEY)
						{
							if(wantedct == 1)
							{
								wantedct = inventory[thisitem].itemcnt;
							} else
							{
								wantedct--;
								Store_WriteSellingCt(items[inventory[thisitem].itemidx].price, wantedct);
							}
						}
					}
				} else
				{
					wantedct=1;
				}
				if(wantedct)
				{
					sayf(SPEECH,"I can pay $%d.\nWould that be okay?\1", items[inventory[thisitem].itemidx].price / 2);
					if(!Inventory_MultipleChoice(21,8,8, 0,1)) //Choice_YesNo))
					{
						MyPlayer.cash += (items[inventory[thisitem].itemidx].price / 2) * wantedct;
						while(wantedct--)
							TakeItem(inventory[cursor+scrolloffset].itemidx);
						sayf(SPEECH,strShopThankYou);
					}
				}
			} else
			{
				sayf(SPEECH, "%s? Oh, no.\nI can't buy that.", items[inventory[thisitem].itemidx].name);
			}
			goto Redraw;
		}
		if(Trg & B_BUTTON)
		{
			break;
		}
		if(Trg & U_KEY)
		{
			vwWrite(6,(cursor+2)*16,strArrowBlank);
			if(cursor==0)
			{
				if(scrolloffset > 0) scrolloffset--;
				Inventory_WriteList(InventoryPages[page].offset, scrolloffset, cursor);
			} else
			{
				cursor--;
			}
			Inventory_ShowItem(inventory[InventoryPages[page].offset+scrolloffset+cursor].itemidx);
			vwWrite(6,(cursor+2)*16,strArrow);
		} else if((Trg & D_KEY) && (inventory[InventoryPages[page].offset+scrolloffset+cursor].itemidx)) //can't pass Cancel.
		{
			vwWrite(6,(cursor+2)*16,strArrowBlank);
			if(cursor==5)
			{
				if(scrolloffset < 40) scrolloffset++;
				Inventory_WriteList(InventoryPages[page].offset, scrolloffset, cursor);
			} else
			{
				cursor++;
			}
			Inventory_ShowItem(inventory[InventoryPages[page].offset+scrolloffset+cursor].itemidx);
			vwWrite(6,(cursor+2)*16,strArrow);
		}
		else if((Trg & L_KEY) && (page>0))
		{
			vwWrite(6,(cursor+2)*16,strArrowBlank);
			page--;
			scrolloffset = 0;
			cursor = 0;
			OamBak[1].CharNo = 64 + (page*64);
			Inventory_WriteList(InventoryPages[page].offset, scrolloffset, cursor);
			Inventory_ShowItem(inventory[InventoryPages[page].offset+scrolloffset+cursor].itemidx);
			vwWrite(6,(cursor+2)*16,strArrow);
			//vwWhiteTransparentLUT();
			//vwWrite(132,32,(char*)InventoryPages[page].name2);
		}
		else if((Trg & R_KEY) && (page < 2)) //set to 4 to allow TMs and Berries without case/pouch
		{
			vwWrite(6,(cursor+2)*16,strArrowBlank);
			page++;
			scrolloffset = 0;
			cursor = 0;
			OamBak[1].CharNo = 64 + (page*64);
			Inventory_WriteList(InventoryPages[page].offset, scrolloffset, cursor);
			Inventory_ShowItem(inventory[InventoryPages[page].offset+scrolloffset+cursor].itemidx);
			vwWrite(6,(cursor+2)*16,strArrow);
			//vwWhiteTransparentLUT();
			//vwWrite(132,32,(char*)InventoryPages[page].name2);
		}
	}
	FadeOut();
	vwNormalLUT();
	ClearOamBak();
	CleanUpCrap();
	return;
}

void DoStore(u16 * inv)
{
	sayf(SPEECH,strShopHiThere);
	while(1)
	{
		switch(MultipleChoice(1,0,14,6,0)) //Choice_BuySellSeeYa))
		{
			case 0:
				FadeOut();
				Store_Buy(inv);
				FadeOut();
				RepairMap();
				break;
			case 1:
				FadeOut();
				Store_Sell();
				FadeOut();
				RepairMap();
				break;
			case 2:
				sayf(SPEECH,strShopComeAgain);
				return;
		}
		sayf(SPEECH,strShopAnythingElse);
	}
}

