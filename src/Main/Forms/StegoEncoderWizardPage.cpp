#include "System.h"
#include "Main/GraphicUserInterface.h"
#include "StegoEncoderWizardPage.h"
#include <fstream>
#include <sstream>

namespace VeraCrypt
{
	StegoEncoderWizardPage::StegoEncoderWizardPage (wxPanel* parent, bool selectExisting)
		: StegoEncoderWizardPageBase (parent),
		SelectExisting (SelectExisting)
	{
		choices.Add(wxT("Option1"));
		choices.Add(wxT("Option2"));
    
		StegoEncoderAlgorithmChoice->Append(choices);
		
		StegoEncoderAlgorithmChoice->Select (0);
	}
	
	wxString GetAvailableAlgorithms(const stego_disk::StegoStorage &stego_storage) 
	{		
		return wxT("asdf");
	}
	
	void StegoEncoderWizardPage::OnFilePathTextChanged(wxCommandEvent &event){
		if(!event.GetString().IsEmpty()){
			SetStegoConfigStatus(_("StegoStorage configured from file."));
		} else {
			SetStegoConfigStatus(_("StegoStorage configured with default parameters."));
		}
	}
	
	void StegoEncoderWizardPage::OnStegoEncoderAlgorithmSelected()
	{
	}
	
	void StegoEncoderWizardPage::OnStegoEncoderAlgorithmHyperlinkClick (wxHyperlinkEvent& event)
	{
		Gui->OpenHomepageLink (this, L"hashalgorithms");
	}
	
	void StegoEncoderWizardPage::SetStegoEncoderAlgorithm (wxString encoder)
	{
		if (true) 
		{
			StegoEncoderAlgorithmChoice->SetStringSelection (encoder);
			OnStegoEncoderAlgorithmSelected();
		}
		
	}
	
	void StegoEncoderWizardPage::OnSelectFileButtonClick (wxCommandEvent& event)
	{
		FilePath path = Gui->SelectVolumeFile (this);

		if (!path.IsEmpty())
			SetFilePath (path);
	}
	
	void StegoEncoderWizardPage::SetFilePath (const FilePath &path)
	{
		FilePathComboBox->SetValue (path.operator wstring());
		PageUpdatedEvent.Raise();
	}
	
}
