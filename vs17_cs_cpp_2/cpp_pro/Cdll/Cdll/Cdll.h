#pragma once
/*
#include <stdlib.h>
#include <string>
#include "atlbase.h"
#include "atlstr.h"
#include "comutil.h"
#include "vcclr.h"
*/
#include <string>
#include <msclr\marshal_cppstd.h>
using namespace System;
using namespace System::Runtime::InteropServices;
using namespace msclr::interop;
#using "./CSdll.dll"
using namespace CSdll;

extern "C" __declspec(dllexport) int c_add(int a, int b) {
	CSdll::Class1 obj;
	return obj.csAdd(a, b);
}

extern "C" __declspec(dllexport) bool c_nist_sch( int numCnt, UInt32* mass,  UInt32* abund, int *resCnt,
	 UInt32* peakNums/*, char ** formula*/) {
	if (numCnt <= 0 || mass == nullptr || abund == nullptr)
		return false;
	array<unsigned int>^ clr_mass = gcnew array<unsigned int>(numCnt);
	array<unsigned int>^ clr_abund = gcnew array<unsigned int>(numCnt);
	for (int i = 0; i < numCnt; i++) {
		clr_mass[i] = *(mass + i);
		clr_abund[i] = *(abund +i);
	}
	// String^ clr_formula = gcnew String(*formula);
	array<unsigned int>^ clr_peakNums;
	CSdll::Class1 obj;
	bool res = obj.nist_sch(clr_mass, clr_abund, *resCnt, clr_peakNums);
	if (*resCnt <= 0)
		return false;
	peakNums = new UInt32(*resCnt);
	for (int i = 0; i < *resCnt; i++) {
		peakNums[i] = clr_peakNums[i];
	}
	Array::Clear(clr_mass, 0, clr_mass->Length);
	Array::Clear(clr_abund, 0, clr_abund->Length);
	Array::Clear(clr_peakNums, 0, clr_peakNums->Length);
	return res;
}

extern "C" __declspec(dllexport) bool c_nist_sch_one(int numCnt, UInt32* mass, UInt32* abund, 
													 int *resCnt, int* CAS, UInt32* MW, 
													 int* Match, char** name, int* name_len, 
													 UInt32* peakNum, int* Prob, int* R_Match, 
													 char** formula, int* formula_len)
{
	if (numCnt <= 0 || mass == nullptr || abund == nullptr)
		return false;
	array<unsigned int>^ clr_mass = gcnew array<unsigned int>(numCnt);
	array<unsigned int>^ clr_abund = gcnew array<unsigned int>(numCnt);
	for (int i = 0; i < numCnt; i++) {
		clr_mass[i] = *(mass + i);
		clr_abund[i] = *(abund + i);
	}

	String^ clr_name = gcnew String("");
	String^ clr_formula = gcnew String("");

	CSdll::Class1 obj;
	bool res = obj.nist_sch_one(clr_mass, clr_abund, *resCnt, *CAS, *MW, *Match, clr_name, *peakNum, *Prob, *R_Match, clr_formula);

	*name_len = clr_name->Length;
	*formula_len = clr_formula->Length;

	int len1 = ((clr_name->Length + 1) * 2);
	*name = new char[len1];
	pin_ptr<const wchar_t> wch = PtrToStringChars(clr_name);
	wcstombs(*name, wch, len1);
	
	int len2 = ((clr_formula->Length + 1) * 2);
	*formula = new char[len2];
	pin_ptr<const wchar_t> wch2 = PtrToStringChars(clr_formula);
	wcstombs(*formula, wch2, len2);

	Array::Clear(clr_mass, 0, clr_mass->Length);
	Array::Clear(clr_abund, 0, clr_abund->Length);
	if (*resCnt <= 0)
		return false;
	return res;
}