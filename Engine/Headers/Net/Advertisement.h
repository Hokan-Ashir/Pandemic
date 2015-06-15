/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'Advertisement' to display ads in your application (for Android and iOS).

/******************************************************************************/
struct Advertisement
{
   enum BANNER_TYPE
   {//TYPE            |    Size   | Description         | Availability
      BANNER          , // 320x50 , Standard Banner     , Phones and Tablets
      MEDIUM_RECTANGLE, // 300x250, IAB Medium Rectangle, Tablets
      FULL_BANNER     , // 468x60 , IAB Full-Size Banner, Tablets
      LEADERBOARD     , // 728x90 , IAB Leaderboard     , Tablets
      SMART_BANNER    , // Varies , Smart Banner        , Phones and Tablets, https://developers.google.com/mobile-ads-sdk/docs/admob/smart-banners
   };
   enum STATE
   {
      NONE   , // ad was not yet requested by the user
      LOADING, // ad is currently being loaded
      DONE   , // ad is available
      ERROR  , // ad failed to load
   };

   Advertisement& testMode(Bool on=true); // 'on'=if enable test mode, which means that you will receive test ads instead of real ones, and won't risk being banned from AdMob for accidental clicking on them

   // banner ad
   STATE          bannerState  (                                        )C {return _banner_state;} // get state of banner ad
   Advertisement& bannerDel    (                                        ); // delete a banner ad
   Advertisement& bannerCreate (C Str8 &unit_id, BANNER_TYPE type=BANNER); // create a banner ad, 'type'=type of the banner, 'unit_id'=ID of the ad (obtained when creating a new ad on the AdMob https://apps.admob.com/ website)
   Advertisement& bannerShow   (                                        ); // show the banner ad, if the ad is not yet loaded, then it will be automatically shown once it gets loaded
   Advertisement& bannerHide   (                                        ); // hide the banner ad
   Advertisement& bannerVisible(Bool visible                            ); // set      banner ad visibility
   Advertisement& bannerPos    (Int  x, Int y                           ); // set      banner ad position, x=-1..1 (-1=left, 0=center, 1=right), y=-1..1 (-1=bottom, 0=center, 1=top), default=(0, 1)
 C VecI2        & bannerPos    ()C {return _banner_pos ;}                  // get      banner ad position, x=-1..1 (-1=left, 0=center, 1=right), y=-1..1 (-1=bottom, 0=center, 1=top), default=(0, 1)
 C VecI2        & bannerSizePx ()C {return _banner_size;}                  // get      banner ad size in pixels, this becomes valid once banner has finished loading (DONE state)

   // fullscreen ad (aka interstitial ad)
   STATE          fsState (               )C {return _fs_state;} // get state of fullscreen ad
   Advertisement& fsDel   (               ); // delete a fullscreen ad
   Advertisement& fsCreate(C Str8 &unit_id); // create a fullscreen ad, 'unit_id'=ID of the ad (obtained when creating a new ad on the AdMob https://apps.admob.com/ website)
   Advertisement& fsShow  (               ); // show the fullscreen ad, if the ad is not yet loaded, then it will be automatically shown once it gets loaded

private:
   Enum1<STATE> _banner_state, _fs_state;
   VecI2        _banner_pos, _banner_size;
   Advertisement();
}extern
   Ads;
/******************************************************************************/
