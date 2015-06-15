/******************************************************************************
 * Copyright (c) Grzegorz Slazinski. All Rights Reserved.                     *
 * Esenthel Engine (http://www.esenthel.com) header file.                     *
/******************************************************************************/
T1(TYPE) struct Node : TYPE // Custom Data Node
{
   Memx<Node> children; // children

   Node& New       (   ) {return children.New();} // create new child
   Node& operator++(Int) {return children.New();} // create new child
};
/******************************************************************************/
