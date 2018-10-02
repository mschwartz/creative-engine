/**
 * BGameEngine
 */
#ifndef GAME_ENGINE_BGAMEENGINE_H
#define GAME_ENGINE_BGAMEENGINE_H

#include "BTypes.h"
#include "BBase.h"
#include "BPlayfield.h"
#include "BSprite.h"
#include "BProcess.h"
#include "Display.h"

#include "BViewPort.h"


class BGameEngine : public BBase {
  friend BPlayfield;
public:
  BGameEngine(BViewPort *aViewPort);

  virtual ~BGameEngine();

public:
  virtual void PreRender();               // called by GameLoop() before anything is done
  virtual void PositionCamera() {}        // called by GameLoop() before actual rendering is done
  virtual void PostRender();              // called by GameLoop() after rendering done, but before Update()
  virtual void GameLoop();                // called once per GApplication's IdleRun()
public:
  void AddProcess(BProcess *aProcess);

  void RunProcessesBefore();

  void RunProcessesAfter();

public:
  void AddSprite(BSprite *aSprite) {
    if (aSprite->flags & SFLAG_SORTY) {  // cause insertion sorted by Y,X
      aSprite->pri = (TInt(aSprite->y) << 16) + TInt(aSprite->x);
    }
    if (aSprite->flags & SFLAG_SORTX) {  // cause insertion sorted by X,Y
      aSprite->pri = (TInt(aSprite->x) << 16) + TInt(aSprite->y);
    }
    mSpriteList->Add(*aSprite);
  }

  void RemoveSprite(BSprite *aSprite) { aSprite->Remove(); }

  void MoveSprites() { mSpriteList->Move(); }

  void AnimateSprites() { mSpriteList->Animate(); }

  void RenderSprites(BViewPort *aViewPort) { mSpriteList->Render(aViewPort); }

  void RenderSprites() { mSpriteList->Render(mViewPort); }

public:
  void Pause() { mPauseFlag = ETrue; }         // no AI, just renders playfield/sprites
  void Resume() { mPauseFlag = EFalse; }       // unpause
  TBool IsPaused() { return mPauseFlag; }

public:
  virtual void Reset();
 
protected:
  TBool mPauseFlag;
public:
  TFloat mWorldXX, mWorldYY;
  TInt32 mFrameCounter;
protected:
  BPlayfield *mPlayfield;
protected:
  TBool mEnabled;
public:
  // disable only calls Game Engine's PreRender() and PostRender() functions.
  void Enable() { mEnabled = ETrue; }

  void Disable() { mEnabled = EFalse; }

  TBool Enabled() { return mEnabled; }

public:
  BViewPort *GetViewPort() { return mViewPort; }

protected:
  BViewPort    *mViewPort;
  Display      *mDisplay;
  BProcessList *mProcessList;
  BSpriteList  *mSpriteList;
};

#endif //GAME_ENGINE_BGAMEENGINE_H
