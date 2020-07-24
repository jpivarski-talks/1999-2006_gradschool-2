#if !defined(LCDROOTACCESS_VECTOR_H)
#define LCDROOTACCESS_VECTOR_H
// -*- C++ -*-
//
// Package:     <LCDRootAccess>
// Module:      Vector
// 
/**\class Vector Vector.h LCDRootAccess/Vector.h

 Description: Pointer class used with extracting a vector from a Record in a Frame

 Usage:
    Use this class to make it easier to extract vector<T*>

    LCDRootAccess::Vector<Foo> foos;
    extract( aRecord, foos);

*/
//
// Author:      
// Created:     Fri Apr 16 15:30:02 EDT 2004
// $Id$
//
// Revision history
//
// $Log$

// system include files
#include <vector>

// user include files

// forward declarations
namespace LCDRootAccess {

template<class T>
class Vector
{
      // ---------- friend classes and functions ---------------

   public:
      // ---------- constants, enums and typedefs --------------
      typedef T value_type ;
      typedef const value_type& const_reference;
      typedef vector<const T*> contents ;
      //typedef VectorItr< T > const_iterator ;

      class const_iterator {
	 public:
	    typedef typename vector<const T*>::const_iterator internal_iterator;
	    typedef typename internal_iterator::difference_type difference_type;
	    typedef const T* pointer;
	    typedef const T& reference;
	    typedef random_access_iterator_tag iterator_category;
	    typedef Vector<T>::const_iterator self;

	    const_iterator(internal_iterator iIt ) : m_iterator(iIt) {}
	    self& operator++() { ++m_iterator; return *this; }
	    self operator++(int) { return self(m_iterator++); }

	    self& operator--() {--m_iterator; return *this; }
	    self operator--(int) {return self(m_iterator--); }

	    self operator+(difference_type iN) const { return (m_iterator+iN); }
	    self& operator+=(difference_type iN ) {
	       m_iterator+= iN; return *this; }
	    
	    self operator-(difference_type iN) const { return (m_iterator-iN); }
	    self& operator-=(difference_type iN ) {
	       m_iterator-= iN; return *this; }

	    bool operator==( const self& iRHS ) const {
	       return m_iterator == iRHS.m_iterator;
	    }
	    bool operator!=( const self& iRHS ) const {
	       return m_iterator != iRHS.m_iterator;
	    }
	    
	    const T& operator*() const { return *(*m_iterator); }
	    const T* operator->() const {return *m_iterator; }
	 private:
	    internal_iterator m_iterator;
      };

      // ---------- Constructors and destructor ----------------
      Vector() :m_vector(0) {}
      Vector(const vector<const T*>* iVector) : m_vector(iVector) {}
      //virtual ~Vector();

      // ---------- member functions ---------------------------
      void setContents( const vector<const T*>* pVector ) {
	 m_vector = pVector; }

      // ---------- const member functions ---------------------
      bool valid() const {return 0 != m_vector; }
      unsigned int size() const {return m_vector->size(); }

      const_iterator begin() const {return m_vector->begin(); }
      const_iterator end() const {return m_vector->end(); }

      const T& front() const { return *(m_vector->front()); }
      const T& back() const {return *(m_vector->back() ); }

      const T& operator[]( unsigned int iIndex ) const {
	 return *(m_vector->operator[](iIndex) ); }

      // ---------- static member functions --------------------

   protected:
      // ---------- protected member functions -----------------

      // ---------- protected const member functions -----------

   private:
      // ---------- Constructors and destructor ----------------
      Vector( const Vector& ); // stop default

      // ---------- assignment operator(s) ---------------------
      const Vector& operator=( const Vector& ); // stop default

      // ---------- private member functions -------------------

      // ---------- private const member functions -------------

      // ---------- data members -------------------------------
      const vector<const T*>* m_vector;

      // ---------- static data members ------------------------

};

// inline function definitions

// Uncomment the following lines, if your class is templated 
// and has an implementation file (in the Template directory)
//#if defined(INCLUDE_TEMPLATE_DEFINITIONS)
//# include "LCDRootAccess/Template/Vector.cc"
//#endif
}
#endif /* LCDROOTACCESS_VECTOR_H */
