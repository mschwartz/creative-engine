#include "CreativeEngine.h"

BMapPlayfield::BMapPlayfield(TUint16 aTilesetSlot, TUint16 aMapSlot, TUint16 aCodesSlot) : BPlayfield() {
  mTilesetSlot = aTilesetSlot;
  mMapSlot = aMapSlot;
  mCodesSlot = aCodesSlot;

  BRaw *rawMap = gResourceManager.GetRaw(aMapSlot);
  TUint16 *pw = (TUint16 *)&rawMap->mData[0];
  mMapWidth = pw[2];
  mMapWidth = pw[3];
  mMapData = &pw[4];

  BRaw *rawAttributes = gResourceManager.GetRaw(aCodesSlot);
  mAttributes = (TUint16 *)&rawAttributes->mData[0];
}

BMapPlayfield::~BMapPlayfield() {
  //
}

void BMapPlayfield::Render(TFloat aWorldX, TFloat aWorldY) {

}