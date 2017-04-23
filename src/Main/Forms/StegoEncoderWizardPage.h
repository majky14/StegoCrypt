/*
 Derived from source code of TrueCrypt 7.1a, which is
 Copyright (c) 2008-2012 TrueCrypt Developers Association and which is governed
 by the TrueCrypt License 3.0.

 Modifications and additions to the original source code (contained in this file)
 and all other portions of this file are Copyright (c) 2013-2016 IDRIX
 and are governed by the Apache License 2.0 the full text of which is
 contained in the file License.txt included in VeraCrypt binary and source
 code distribution packages.
*/

#ifndef TC_HEADER_Main_Forms_StegoEncoderWizardPage
#define TC_HEADER_Main_Forms_StegoEncoderWizardPage

#include "Forms.h"
#include "stego_storage.h"

namespace VeraCrypt
{
	class StegoEncoderWizardPage : public StegoEncoderWizardPageBase
	{
	public:
		StegoEncoderWizardPage (wxPanel* parent, bool selectExisting = false);
		wxString GetStegoEncoder ();
		bool IsValid () { return true; }
		void SetPageText (const wxString &text) { }
		void SetStegoEncoderAlgorithm (wxString encoder);
		wxString GetAvailableAlgorithms (const stego_disk::StegoStorage &stego_storage);
		void SetFilePath (const FilePath &path);
		FilePath GetStegoConfigFilePath () const { return FilePath (wstring (FilePathComboBox->GetValue()));}

	protected:
		void OnStegoEncoderAlgorithmSelected ();
		void OnStegoEncoderAlgorithmSelected (wxCommandEvent& event) { OnStegoEncoderAlgorithmSelected(); }
		void OnStegoEncoderAlgorithmHyperlinkClick (wxHyperlinkEvent& event);
		void OnFilePathTextChanged (wxCommandEvent& event);
		void OnSelectFileButtonClick (wxCommandEvent& event);
		void SetStegoConfigStatus(const wxString &text) { StegoConfigStatusStaticText->SetLabel(text); }
		
		bool SelectExisting;
		
	private:
		wxArrayString choices;
	};
}
#endif // TC_HEADER_Main_Forms_StegoEncoderWizardPage
