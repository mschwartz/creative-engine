#ifndef BRESOURCEMANAGER_H
#define BRESOURCEMANAGER_H

/**
 * Resource Management.
 *
 * Resources are arbitrary files that are packed into a bundle of resource by
 * the resource compiler tool (tools/rcomp).
 *
 * The bundle is then included in the app/game as raw binary, using the
 * COMPONENT_EMBED_FILES define in the component.mk for the game.
 */
#include "BBase.h"
#include "BBitmap.h"

// Each resource that is loaded requires allocated RAM, so we don't want to just load them all
// from the FLASH/ROM/RODATA all at once.

// Maximum number of resources that can be loaded at one time
static const int MAX_RESOURCE = 1024;

// Image type, passed as argument to LoadBitmap().
static const TInt16 IMAGE_ENTIRE = 0; // image is the entire bitmap in width, height
static const TInt16 IMAGE_8x8    = 1; // bitmap contains individual images, each 8x8, on a grid
static const TInt16 IMAGE_16x16  = 2; // "" 16x16 on a grid
static const TInt16 IMAGE_32x32  = 3; // etc.
static const TInt16 IMAGE_64x64  = 4;
static const TInt16 IMAGE_8x16   = 5;
static const TInt16 IMAGE_16x8   = 6;
static const TInt16 IMAGE_8x32   = 7;
static const TInt16 IMAGE_32x8   = 8;
static const TInt16 IMAGE_8x64   = 9;
static const TInt16 IMAGE_64x8   = 10;
static const TInt16 IMAGE_16x32  = 11;
static const TInt16 IMAGE_32x16  = 12;
static const TInt16 IMAGE_16x64  = 13;
static const TInt16 IMAGE_64x16  = 14;
static const TInt16 IMAGE_32x64  = 15;
static const TInt16 IMAGE_64x32  = 16;
static const TInt16 IMAGE_32x40  = 17;

struct BitmapSlot;

// maximum number of bitmaps loaded at any given time
#define MAX_BITMAP_SLOTS 16

class BResourceManager : public BBase {
public:
  // construct a resource manager from data in ROM (FLASH)
  BResourceManager(TAny *aROM);

  ~BResourceManager();

public:
  // Load a bitmap from Flash into a slot.  From this point forward, refer to the bitmap
  // by the slot ID in application code.
  TBool LoadBitmap(TInt16 aReosurceId, TInt16 aSlotId, TInt16 aImageType = IMAGE_ENTIRE);

  // Assign an already loaded BBitmap to a slot.  In theory, these would be RAM based bitamaps.
  // These bitmaps WILL be released, if not cached, meaning they will be (operator) delete.
  TBool SetBitmap(BBitmap *aBitmap, TInt16 aSlotId, TInt16 aImageType = IMAGE_ENTIRE);

  // Unload a bitmap from a slot, releasing any resources/memory it uses.
  // Caveat Progammer: This will NOT unload a cached bitmap!
  TBool ReleaseBitmap(TInt16 aSlotId);

  // Unload all non-cached bitmaps slots.
  void ReleaseBitmaps();

  // Cache an already loaded bitmap, so ReleaseBitmaps() won't free it.
  TBool CacheBitmapSlot(TInt16 aSlotId, TBool aCacheIt = ETrue);

  // Clear (or set) cached status of all loaded bitmaps
  void ClearCache(TBool aCacheIt = EFalse);

  // Get an already loaded bitmap, given the slot number
  BBitmap *GetBitmap(TInt16 aSlotId);

  // Get width of image at slot.  If bitmap is a grid of images, then the width of the grid is returned.
  // That is, if the bitmap has 32x32 images on it, then 32 is returned.
  TInt BitmapWidth(TInt aSlotId);

  // Get height of image at slot.  If bitmap is a grid of images, then the height of the grid is returned.
  // That is, if the bitmap has 32x32 images on it, then 32 is returned.
  TInt BitmapHeight(TInt aSlotId);

protected:
  TInt32     mNumResources;    // number of resources
  TUint32    *mResourceTable; // table of offsets into mROM of resources
  TUint8     *mROM;
  BitmapSlot *mBitmapSlots[MAX_BITMAP_SLOTS];
//  BBitmap *bitmaps[MAX_RESOURCE];
};

extern "C" {
extern TUint8           binary_blob_bin_start[];
}
extern BResourceManager resourceManager;
#endif
