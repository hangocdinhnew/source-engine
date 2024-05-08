#include "cbase.h"

#include "beam_shared.h"

#include "Sprite.h"

#include "tier0/memdbgon.h"

class CFuncFunction : public CBaseEntity {
public:
  DECLARE_CLASS(CFuncFunction, CBaseEntity);
  DECLARE_DATADESC();

  void Precache(void);
  void Spawn(void);
  void DrawSprites(void);
  void Function(float A, float P);
  void Think(void);

  void AddA(inputdata_t &inputdata);

protected:
  float sinCoeff;
  float sinTimeCoeff;
  float length;
  float phase;
  Vector zeroPoint;

  CSprite *pStartSprite;
  CSprite *pEndSprite;
};

LINK_ENTITY_TO_CLASS(func_function, CFuncFunction);

BEGIN_DATADESC(CFuncFunction)
DEFINE_KEYFIELD(sinCoeff, FIELD_FLOAT, "sinCoeff"),
    DEFINE_FIELD(sinTimeCoeff, FIELD_FLOAT), DEFINE_FIELD(length, FIELD_FLOAT),
    DEFINE_FIELD(phase, FIELD_FLOAT),
    DEFINE_FIELD(zeroPoint, FIELD_POSITION_VECTOR),

    DEFINE_INPUTFUNC(FIELD_VOID, "AddA", AddA), DEFINE_THINKFUNC(Think),

    END_DATADESC()

        void CFuncFunction::Precache() {
  BaseClass::Precache();
  PrecacheMaterial("sprites/laserbeam.vmt");
}

void CFuncFunction::Spawn(void) {
  BaseClass::Spawn();
  zeroPoint = GetAbsOrigin();

  sinCoeff = 20;
  sinTimeCoeff = 2;
  length = 360;
  phase = 35;

  DrawSprites();
  Function(sinCoeff, phase);
  SetThink(&CFuncFunction::Think);
  SetNextThink(gpGlobals->curtime);
}

void CFuncFunction::DrawSprites(void) {
  pStartSprite =
      CSprite::SpriteCreate("sprites/blueflare1.vmt", zeroPoint, false);
  pStartSprite->SetScale(1);
  pStartSprite->SetTransparency(kRenderGlow, 0, 0, 255, 255,
                                kRenderFxNoDissipation);

  pEndSprite =
      CSprite::SpriteCreate("sprites/blueflare1.vmt", zeroPoint, false);
  pEndSprite->SetScale(1);
  pEndSprite->SetTransparency(kRenderGlow, 0, 0, 255, 255,
                              kRenderFxNoDissipation);
}

void CFuncFunction::Function(float A, float P) {
  const int subdivisions = 35;
  Vector positions[subdivisions + 1];
  const float spacing = length;

  for (int i = 0; i <= subdivisions; i++) {
    float angleToUse = i * spacing;

    positions[i].y = zeroPoint.y + (angleToUse);
    positions[i].x = zeroPoint.x;

    float sinBit =
        A * sin(DEG2RAD(angleToUse + (sinTimeCoeff * P * gpGlobals->curtime)));
    float cosBit =
        A * cos(DEG2RAD(angleToUse - (sinTimeCoeff * P * gpGlobals->curtime)));
    positions[i].z = zeroPoint.z + (sinBit * cosBit);
  }

  for (int i = 0; i < subdivisions; i++) {
    CBeam *pBeam = CBeam::BeamCreate("sprites/laserbeam.vmt", 1);
    pBeam->PointsInit(positions[i], positions[i + 1]);
    pBeam->RelinkBeam();
    pBeam->SetBrightness(255);
    pBeam->SetColor(255, 255, 255);
    pBeam->LiveForTime(0.1f);
  }

  pStartSprite->SetLocalOrigin(positions[0]);
  pEndSprite->SetLocalOrigin(positions[subdivisions]);
}

void CFuncFunction::Think(void) {
  Function(sinCoeff, phase);
  SetNextThink(gpGlobals->curtime + 0.1);
}

void CFuncFunction::AddA(inputdata_t &inputdata) { sinCoeff++; }
