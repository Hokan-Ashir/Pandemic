/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
struct Aggregate
{
   void del();
   Aggregate() {_aggr=NULL;}
  ~Aggregate() {del();}
private:
   Ptr _aggr;
   NO_COPY_CONSTRUCTOR(Aggregate);
};
/******************************************************************************/
