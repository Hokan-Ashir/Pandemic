/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************

   Use 'EsenthelStore' to communicate with Esenthel Store.
      You can use it for example if you've developed a game which is sold in Esenthel Store,
      and in the game you'd like to verify if it's a licensed copy.

      This testing can be done for example in following way:
         1. Ask the user for license key
         2. Test that license key (optionally with Computer ID of the users computer)
         3. Allow to play the game only based on successful response from Esenthel Store

/******************************************************************************/
struct EsenthelStore // class allowing to communicate with Esenthel Store
{
   enum RESULT
   {
      NONE                      , // nothing was ordered yet
      INVALID_ITEM              , // 'item_id' is invalid
      INVALID_LICENSE_KEY_FORMAT, // 'license_key' was specified however it is not of the "XXXXX-XXXXX-XXXXX-XXXXX-XXXXX" format
      INVALID_EMAIL_FORMAT      , // 'email'       was specified however it is not of correct format
      CONNECTING                , // connecting to Esenthel Store at the moment
      CANT_CONNECT              , // could not connect to Esenthel Store
      INVALID_RESPONSE          , // received an invalid response from Esenthel Store
      EMAIL_NOT_FOUND           , // Esenthel Store replied that given email was not found
      LICENSE_KEY_FAIL          , // Esenthel Store replied that given license is not valid for the specified item
      COMPUTER_ID_FAIL          , // Esenthel Store replied that given license is     valid for the specified item however ComputerID did not match   the one in the store
      CONFIRM_CODE_FAIL         , // Esenthel Store replied that given license is     valid for the specified item and     ComputerID         matches the one in the store however confirmation code was incorrect (this may be caused by user having invalid time/date/timezone on his computer)
      OK                        , // Esenthel Store replied that given license is     valid for the specified item and     ComputerID         matches the one in the store and     confirmation code was   correct
   };

   static Str ComputerID() {return EE::ComputerID(true).asHex();} // get Computer ID used in Esenthel Store, you can use this function to get the ID of current computer and display it to the users, so they can set it for their products in Esenthel Store if needed

   // operations
   void clear      (Bool params=true); // clear any current test request and the result to NONE, 'params'=if additionally clear the last specified parameters (such as 'itemID', 'licenseKey' and 'email')
   void testLicense(Int  item_id, C Str &license_key=S, C Str &email=S, Bool computer_id=false); // test if license is ok for a given item in Esenthel Store, 'item_id'=id of an item in Esenthel Store (if you're the author of the item, then you can get its ID from Esenthel Store), following parameters are optional, only one of them needs to be specified (for example you can test only license key, only email, only computer id, or multiple at the same time), 'license_key'=if specified (must be of "XXXXX-XXXXX-XXXXX-XXXXX-XXXXX" format) then the license key will be tested if it's valid for the specified item in Esenthel Store, 'email'=test if there exists a user account with specified email address which has a valid license key for specified item, 'computer_id'=test if Computer ID of current machine matches the one assigned to the license key, once this function is called it will try to connect to Esenthel Store on a secondary thread to verify the data, while it's running you can investigate the 'result' method to get the results

   // get
   RESULT result    (); // get result of the test
   Int    itemID    ()C {return _item_id    ;} // get item    id  that was specified in the last request
 C Str&   licenseKey()C {return _license_key;} // get license key that was specified in the last request
 C Str&   email     ()C {return _email      ;} // get email       that was specified in the last request

   EsenthelStore();

private:
   Bool     _computer_id;
   Int      _item_id;
   UInt     _r;
   RESULT   _result;
   Str      _license_key, _email;
   Download _down;
};
/******************************************************************************/
