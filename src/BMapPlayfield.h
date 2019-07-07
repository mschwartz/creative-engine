#ifndef BMAPPLAYFIELD_H
#define BMAPPLAYFIELD_H

#include <BPlayfield.h>
#include <Display/DisplayDefines.h>

// Playfield is a map of width,height 16x16 tiles
// TODO: 32x32 tiles, 64x64 tiles, etc.
class BMapPlayfield : public BPlayfield {
public:
  BMapPlayfield(TUint16 aTilesetSlot, TUint16 aMapSlot, TUint16 aCodesSlot);

  virtual ~BMapPlayfield();

public:
  // in pixels
  TUint16 TileSize() { return 16; }
  TUint16 MapWidth() { return mMapWidth * 16; }
  TUint16 MapHeight() { return mMapHeight * 16; }
  TUint16 MapMaxX() { return mMapWidth * 16 - SCREEN_WIDTH; }
  TUint16 MapMaxY() { return mMapHeight * 16 - SCREEN_HEIGHT; }

  // in tiles
  TUint16 MapWidthTiles() { return mMapWidth; }
  TUint16 MapHeightTiles() { return mMapHeight; }

public:
  void Render(TFloat aWorldX, TFloat aWorldY);

protected:
  TUint16 mTilesetSlot;
  TUint16 mMapSlot;
  TUint16 mCodesSlot;
  TUint16 mMapWidth, mMapHeight;
  TUint16 *mMapData;
  TUint16 *mAttributes;
};

#endif //BMAPPLAYFIELD_H
