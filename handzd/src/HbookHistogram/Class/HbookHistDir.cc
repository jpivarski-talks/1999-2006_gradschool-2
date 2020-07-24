// -*- C++ -*-
//
// Package:     HbookHistogram
// Module:      HbookHistDir
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Chris D Jones
// Created:     Mon Sep 27 17:41:24 EDT 1999
// $Id: HbookHistDir.cc,v 1.15 2003/03/14 17:47:40 vk Exp $
//
// Revision history
//
// $Log: HbookHistDir.cc,v $
// Revision 1.15  2003/03/14 17:47:40  vk
// Fix sstream for OSF using USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG & strstream.h
//
// Revision 1.14  2003/03/12 21:51:41  vk
// Add truncated algorithm for HBOOK/Directory names
//
// Revision 1.13  2001/07/21 15:47:26  cdj
// conform to new HIHistDir interface
//
// Revision 1.12  2000/03/16 21:05:29  dlk
// Repair error determining length of directory string (CDJ)
//
// Revision 1.11  2000/03/15 18:55:35  cdj
// fixed case where put histograms into root directory
//
// Revision 1.10  2000/03/11 18:04:32  cdj
// <This log should have been with the previous change>
// -Speed up makeDirDefault by a factor of 20.
//   -This was necessary since makeDirDefault was dominating the time it took to
//    fill a histogram
//   -Unfortunately it takes too much time to check every time to see if hcdir_
//    has been called by someone other than HbookHistDir.  To try to catch
//    problems, I check once out of 2000 calls to makeDirDefault to see if
//    hbook and C++ agree on what the present directory is.
//
// Revision 1.9  2000/03/11 18:00:35  cdj
// HbookHistDir.cc
//
// Revision 1.8  2000/02/01 02:48:42  cdj
// every HbookManager now has its own Zebra root directory
//
// Revision 1.7  2000/01/31 22:55:31  cdj
// made it safer for two HbookManagers to share the root directory
//
// Revision 1.6  1999/10/29 22:13:31  cdj
// now issue warning message if directory name is longer than 16 characters
//
// Revision 1.5  1999/10/07 18:07:50  hufnagel
// Numbers now use float instead of double
//
// Revision 1.4  1999/10/07 17:44:15  mkl
// allow repeated calls to setDefaultDir method; fix up warning message about changing ids when id is already taken
//
// Revision 1.3  1999/10/01 19:23:13  cdj
// plugged memory leaks and histograms without ids works
//
// Revision 1.2  1999/09/30 18:00:48  mkl
// give INFO message when a next id has to be assigned
//
// Revision 1.1  1999/09/29 17:55:46  cdj
// added histogram directories
//

#include "Experiment/Experiment.h"

// system include files
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#include <vector>
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */
#include <assert.h>

// user include files
#include "Experiment/report.h"
#include "HbookHistogram/HbookHistDir.h"

#include "HbookHistogram/hbook_functions.h"
#include "HbookHistogram/HbookHist1D.h"
#include "HbookHistogram/HbookHist2D.h"
#include "HbookHistogram/HbookHistProf.h"
#include "HbookHistogram/HbookNtuple.h"
#include "HbookHistogram/HbookFile.h"
#include "DummyHistogram/DummyNumber.h"
#include "DummyHistogram/DummyNumberWithErrors.h"


// STL classes
#include <vector>
#include <string>
#if defined(USE_STRSTREAM_RATHER_THAN_STRINGSTREAM_BUG)
#include <strstream.h>
#else
#include <sstream>
#endif

//
// constants, enums and typedefs
//

static const char* const kFacilityString = "HbookHistogram.HbookHistDir" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: HbookHistDir.cc,v 1.15 2003/03/14 17:47:40 vk Exp $";
static const char* const kTagString = "$Name:  $";

static const unsigned int kMaxNameLength = 16;

//
// static data member definitions
//
const HbookHistDir*
HbookHistDir::s_defaultDir = 0;

DABoolean
HbookHistDir::s_fileDirIsDefault = false;

//
// constructors and destructor
//
HbookHistDir::HbookHistDir( HbookFile* iFile ) :
   HIHistDir( "root" ),
   m_file( iFile ),
   m_nextId( 1 )
{
   assert( 0 != iFile );
   
   //set to hbook's root memory directory
   m_path = string("//PAWC");
   hcdir_(m_path.c_str(), " ", m_path.size(), 1 );

   m_path = m_path + "/" + m_file->getTopDir();

   //make sure the root which holds our memory histograms is unique
   hmdir_(m_file->getTopDir(), " ", 
	  strlen(m_file->getTopDir()), 1 );

   //set to the root directory for the file
   m_filePath = string( "//") + string(m_file->getTopDir() ) ;

   makeDirDefault();

}

HbookHistDir::HbookHistDir( const string& iName, 
			    HbookHistDir* iParent,
			    HbookFile* iFile ) :
   HIHistDir( iName ),
   m_file( iFile ),
   m_nextId( 1 )
{
   assert( 0 != iParent );

   string hbookName = iName;
   //check to make sure the name fits within hbook size limit

   if( iName.size() > kMaxNameLength ) {
//      hbookName = iName.substr(0, kMaxNameLength);
      hbookName = makeShortName(iName);
      report( WARNING, kFacilityString ) << "\ndirectory name "
					 << iName
					 << " exceeds hbook size limit of "
					 << kMaxNameLength
					 << "\nname has been truncated to "
					 << hbookName << endl;
   } 

   m_path = iParent->m_path + string("/") + hbookName;
   m_filePath = iParent->m_filePath + string("/") + hbookName;
   
   //create the directory in the file
   iParent->makeFileDirDefault();
   hmdir_(hbookName.c_str(), " ", hbookName.size(), 1 );
      
   
   iParent->makeDirDefault();
   //tell hbook about this directory
   hmdir_(hbookName.c_str(), " ", hbookName.size(), 1 );


}

// HbookHistDir::HbookHistDir( const HbookHistDir& rhs )
// {
//    // do actual copying here; if you implemented
//    // operator= correctly, you may be able to use just say      
//    *this = rhs;
// }

HbookHistDir::~HbookHistDir()
{
   makeDirDefault();
   makeFileDirDefault();

   //store all the histograms in this directory
   
   FInteger id = 0;
   FInteger icycle = 0;
   hrout_( &id, &icycle, " ", 1 );

}

//
// assignment operators
//
// const HbookHistDir& HbookHistDir::operator=( const HbookHistDir& rhs )
// {
//   if( this != &rhs ) {
//      // do actual copying here, plus:
//      // "SuperClass"::operator=( rhs );
//   }
//
//   return *this;
// }

//
// member functions
//
HIHistDir*
HbookHistDir::makeDir( const string& iName )
{
   HbookHistDir* temp = new HbookHistDir( iName, this, m_file );

   return temp;
}

// 1D histogram
HIHist1D* 
HbookHistDir::makeHistogram( Count iId,
			 const string&  iTitle,
			 unsigned int   iNChannels,
			 float          iLowEdge,
			 float          iHighEdge,
			 float          iBitsPerChannel )
{ 
   makeDirDefault();
   Count id = checkValidId( iId );

   HbookHist1D* hist( new HbookHist1D( this,
				       id,
				       iTitle,
				       iNChannels,
				       iLowEdge,
				       iHighEdge,
				       iBitsPerChannel ) ) ;
   
   return ( hist ) ;
}

// 2D histogram
HIHist2D* 
HbookHistDir::makeHistogram( Count         iId,
			 const string& iTitle,
			 unsigned int  iNChannelsX,
			 float         iLowEdgeX,
			 float         iHighEdgeX,
			 unsigned int  iNChannelsY,
			 float         iLowEdgeY,
			 float         iHighEdgeY,
			 float         iBitsPerChannel )
{ 
   makeDirDefault();
   Count id = checkValidId( iId );
   
   HbookHist2D* hist( new HbookHist2D( this,
				       id,
				       iTitle,
				       iNChannelsX,
				       iLowEdgeX,
				       iHighEdgeX,
				       iNChannelsY,
				       iLowEdgeY,
				       iHighEdgeY,
				       iBitsPerChannel ) );
   
   return ( hist ) ;
}

// profile histogram
HIHistProf* 
HbookHistDir::makeProfile( Count         iId,
		       const string& iTitle,
		       unsigned int  iNChannels,
		       float         iLowEdgeX,
		       float         iHighEdgeX,
		       float         iLowEdgeY,
		       float         iHighEdgeY,
		       HIHistProf::DisplayErrorsAs iDisplayErrorsAs )
{ 
   makeDirDefault();
   Count id = checkValidId( iId );
   
   HbookHistProf* hist( new HbookHistProf( this,
					   id,
					   iTitle,
					   iNChannels,
					   iLowEdgeX,
					   iHighEdgeX,
					   iLowEdgeY,
					   iHighEdgeY,
					   iDisplayErrorsAs) ) ;
   
   return ( hist ) ;
}

// ntuple 
HINtuple* 
HbookHistDir::makeNtuple( Count         iId,
		      const string& iTitle,
		      unsigned int  iNumberOfVariables,
		      unsigned int  iChunkSize,
		      const char* const*  iLabels )
{ 
   makeDirDefault();
   Count id = checkValidId( iId );
   
   HbookNtuple* hist( new HbookNtuple( this,
				       *m_file,
				       iId,
				       iTitle,
				       iNumberOfVariables,
				       iChunkSize,
				       iLabels ) ) ;
   
   return ( hist ) ; 
}

HINumber* 
HbookHistDir::makeNumber( const string& iName,
		      float         iValue )
{ 
   DummyNumber* number( new DummyNumber( iName,
					 iValue ) );
   
   return number;
}

HINumberWithErrors* 
HbookHistDir::makeNumberWithErrors( const string& iName,
				float         iValue,
				float         iPositiveError,
				float         iNegativeError )
{ 
   DummyNumberWithErrors* numberWithErrors =
      new DummyNumberWithErrors( iName,
				 iValue,
				 iPositiveError,
				 iNegativeError );
   
   return numberWithErrors;
}

Count 
HbookHistDir::nextId()
{
   while( m_nextId <= 0 || idExists( m_nextId ) ) {
      ++m_nextId ;
   }

   return m_nextId;
}

DABoolean
HbookHistDir::idExists( Count iId ) const
{
   int id = iId; // hexist_ function wants an "int"
   DABoolean returnValue = (hexist_( &id ) & 0x1 ) ? true:false;

   return returnValue;
}

Count
HbookHistDir::checkValidId( Count iId )
{
   Count returnValue = iId;

   if( iId <= 0 )
   {
      //report( WARNING, kFacilityString )
      // << "id<=0; will use next available positive id!" 
      // << endl;
      returnValue = nextId();
   }
   else
   {
      // make sure the next id is valid
      if( true == idExists( iId ) )
      {
	 returnValue = nextId();
      }
      else
      {
	 returnValue = iId; 
      }
   }

   // print message when id was changed
   if( iId != returnValue )
   {
      report( INFO, kFacilityString )
	 << "Directory: " << name() << ": "
	 << "id already taken, using next available: " << m_nextId 
	 << endl;
   }

   return returnValue;
}

//
// const member functions
//

//moved this variable out of makeDirDefault to speed up the routine
static unsigned int lastTimeChecked( 0 );

void
HbookHistDir::makeDirDefault() const {
   //This check frequency causes hcdir to eat up 1% of the time of this call
   // if no actually directory change is needed
   const unsigned int kCheckFrequency = 2000;
   
   if( ( (++lastTimeChecked) > kCheckFrequency ) && ( 0 != s_defaultDir) ) {
      if( false == s_fileDirIsDefault ) {
	 lastTimeChecked = 0;

	 //make sure the present directory is what we expect it to be
	 const FInteger kMaxPresentDirLength= kMaxNameLength*4;
	 char presentDir[ kMaxPresentDirLength ];
	 
	 hcdir_( presentDir, "R", kMaxPresentDirLength, 1 );

	 //If this assert fails it means you should increase the size of
	 //  kMaxPresentDirLength
	 assert( kMaxPresentDirLength >= s_defaultDir->m_path.size() );

	 //see if the directory path from hcdir matches our C++ default path
	 DABoolean defaultHbookDirectoryIsCorrect =  
	    ( 0 == strncmp(s_defaultDir->m_path.c_str(), 
			   presentDir, 
			   s_defaultDir->m_path.size() ) );

	 if( !defaultHbookDirectoryIsCorrect  ) {
	    report( EMERGENCY, kFacilityString ) << "default HBook directory is incorrect \""<< presentDir <<"\""
                                             << "\nshould be "<<s_defaultDir->m_path<<endl;
	    assert(defaultHbookDirectoryIsCorrect);
	    ::exit(-1);
	 }
      } else {
	 //try it next time
	 --lastTimeChecked;
      }
   }
   
   //see if we are already using the present directory
   if( s_defaultDir != this || s_fileDirIsDefault == true ) {
      
      hcdir_( m_path.c_str(), " ", m_path.size(), 1 ); 
      s_defaultDir = this;
      s_fileDirIsDefault = false;
   }
   
}

string 
HbookHistDir::makeShortName(const string& iName) const {

  string dirName = iName;
  if(dirName.size()<=kMaxNameLength) return dirName;
  
  // define shortName and tag (which we'll keep untouched as much as we can)
  int iSearch = dirName.find("@");
  string tag="", shortName=dirName;
  if(iSearch!=string::npos) {
    tag.assign(dirName,iSearch,dirName.size());
    shortName.replace(iSearch,shortName.size()-iSearch,"");
  }

  report( DEBUG, kFacilityString )    
    <<"incoming name "<<endl
    <<"dirName "<<shortName+tag<<" shortName "<<shortName<<" tag "<<tag<<endl;
  
  // define max size of short name
  int kMaxSize = kMaxNameLength-tag.size();

  // remove from shortName "Proc"
  string proc = "Proc";
  int j = shortName.find(proc);
  if( j!= string::npos ) shortName.erase(j,proc.size()); 

  report( DEBUG, kFacilityString )    
    <<"first check when we remove Proc "<<endl
    <<"dirName "<<shortName+tag<<" shortName "<<shortName<<" tag "<<tag<<endl;

  // first check when we remove "Proc"
  if(shortName.size()<=kMaxSize) return shortName+tag;
     
  // remove every vowels in shortName except first (if any) until reach size of kMaxSize
  shortName = removeVowel(shortName, kMaxSize);

  report( DEBUG, kFacilityString )    
    <<"check when we remove vowel in shortName "<<endl
    <<"dirName "<<shortName+tag<<" shortName "<<shortName<<" tag "<<tag<<endl;

  // check again when we removed vowels
  if(shortName.size()<=kMaxSize) return shortName+tag;

  // remove all lower case letters which are immediately followed by another lower case letter
  shortName = removeLower(shortName, kMaxSize);

  report( DEBUG, kFacilityString )    
    <<"check when we remove lower case letters in shortName "<<endl
    <<"dirName "<<shortName+tag<<" shortName "<<shortName<<" tag "<<tag<<endl;

  // check again when we removed double lower case letters
  if(shortName.size()<=kMaxSize) return shortName+tag;

  // remove every vowels in a tag except first (if any) until reach size of kMaxSize
  tag = removeVowel(tag,kMaxNameLength-shortName.size());

  report( DEBUG, kFacilityString )    
    <<"check when we remove vowel in a tag "<<endl
    <<"dirName "<<shortName+tag<<" shortName "<<shortName<<" tag "<<tag<<endl;
  
  // check again when we removed all vowels in a tag
  dirName = shortName+tag;
  if(dirName.size()<=kMaxNameLength) return dirName;

  // remove all lower case letters in shortName
  shortName = removeAllLower(shortName,kMaxNameLength-tag.size());

  report( DEBUG, kFacilityString )    
    <<"check when we remove all lower case letters in a shortName "<<endl
    <<"dirName "<<shortName+tag<<" shortName "<<shortName<<" tag "<<tag<<endl;
  
  // check again when we removed all lower case letters in a shortName
  dirName = shortName+tag;
  if(dirName.size()<=kMaxNameLength) return dirName;
  
  // remove all lower case letters which are immediately followed by another lower case letter
  // do it in a tag
  tag = removeLower(tag,kMaxNameLength-shortName.size());

  report( DEBUG, kFacilityString )    
    <<"check when we remove lower case letters in a tag "<<endl
    <<"dirName "<<shortName+tag<<" shortName "<<shortName<<" tag "<<tag<<endl;

  // check again when we removed all lower case letters in a shortName
  dirName = shortName+tag;
  if(dirName.size()<=kMaxNameLength) return dirName;

  // finally if we exceed 8 characters remove letter from the back of shortName
  kMaxSize  = kMaxNameLength-tag.size();
  if(shortName.size()>kMaxSize)
     shortName.erase(kMaxSize,shortName.size()-kMaxSize);
     
  return shortName+tag;
                
}


string
HbookHistDir::removeVowel(const string& iName, const int& kMaxSize) const {

  string shortName = iName;
  // remove every vowels in shortName except first (if any) until reach size of kMaxSize
  DABoolean firstL = false;
  if(shortName.size()>kMaxSize) {
    string firstLetter;
    firstLetter.assign(shortName,0,1);
    if(firstLetter.find_first_of("aeiou") != string::npos) firstL = true;
    int k=0;
    do {
      k = shortName.find_first_of("aeiou");
      if( k != string::npos ) shortName.erase(k,1);
      if(firstL) {
        // we found that firstLetter was vowel
        if(shortName.size()<=kMaxSize-1) break;
      } else {
        // we didn't find that firstLetter was vowel
        if(shortName.size()<=kMaxSize) break;
      }
    } while( k != string::npos );
    if(firstL) shortName = firstLetter+shortName;
  }
  return shortName;
}

string
HbookHistDir::removeLower(const string& iName, const int& kMaxSize) const {

  string shortName = iName;
  // remove all lower case letters which are immediately followed by another lower case letter
  if(shortName.size()>kMaxSize) {
    int k = 0, j = 0, i = 0;
    do {
      // we start search from first occurance of lower case letter except
      // it's first letter in a word
      k = shortName.find_first_of("qwrtpsdfghjklzxcvbnm",i+1);
      j = shortName.find_first_of("qwrtpsdfghjklzxcvbnm",k+1);
      i = k; // next search start from this position
      if(k!=string::npos && j!=string::npos && j-k==1) {
        shortName.erase(k,1); 
        i=k-1; // step back since we remove one letter
      }
      if(shortName.size()<=kMaxSize || k==string::npos) break;
    } while( k != string::npos );
  }
  return shortName;
}

string
HbookHistDir::removeAllLower(const string& iName, const int& kMaxSize) const {

  string shortName = iName;
  // remove all lower case letters in shortName
  if(shortName.size()>kMaxSize) {
    int k = 0;
    do {
      k = shortName.find_first_of("qwrtpsdfghjklzxcvbnm");
      if(k!=string::npos) shortName.erase(k,1);
      if(shortName.size()<=kMaxSize) break;
    } while( k != string::npos );
  }
  return shortName;
}

//
// static member functions
//
