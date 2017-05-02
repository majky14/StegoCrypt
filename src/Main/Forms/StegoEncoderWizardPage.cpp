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
		vector<string> AvailableEncoders = stego_disk::EncoderFactory::GetEncoderNames();
		foreach(string encName, AvailableEncoders)
		{
			
			StegoEncoderAlgorithmChoice->Append(encName);
		}
		StegoEncoderAlgorithmChoice->Select (0);
		
		StegoEncoderAlgorithmStaticText->SetLabel("Allows you to configure Stego with provided encoder settings.");
		StegoParamsFromFileStaticText->SetLabel("Allows you to configure Stego in more detail by providing JSON configuration file.");//Specify a file path containing StegoParams configuration file in JSON format.");
		StegoRadioButton_Manual->SetValue(true);
		StegoEncoderAlgorithmChoice->Enable(true);
		FilePathComboBox->Enable(false);
		SelectFileButton->Enable(false);
	}
	
	wxString GetAvailableAlgorithms(const stego_disk::StegoStorage &stego_storage) 
	{		
		return wxT("asdf");
	}

	wxString StegoEncoderWizardPage::GetEncoderAlgorithm(){
		using namespace stego_disk;
		vector<string> allEncoders = stego_disk::EncoderFactory::GetEncoderNames(); 
		std::string encoder = allEncoders[StegoEncoderAlgorithmChoice->GetSelection()];
		
		return encoder;
	}
	
	void StegoEncoderWizardPage::OnFilePathTextChanged(wxCommandEvent &event) {
		if(!event.GetString().IsEmpty()){
			SetStegoConfigStatus(_("StegoStorage configured from file."));
		} else {
			encoderName = GetEncoderAlgorithm();
			SetStegoConfigStatus(_("StegoStorage configured with "+encoderName+" encoder."));
			StegoEncoderAlgorithmHyperlink->SetLabel("More information about "+encoderName);
		}
	}
	
	void StegoEncoderWizardPage::OnStegoEncoderAlgorithmSelected(wxCommandEvent &event)
	{
		if(!event.GetString().IsEmpty() && FilePathComboBox->IsTextEmpty()){
			encoderName = GetEncoderAlgorithm();
			SetStegoConfigStatus(_("StegoStorage configured with "+encoderName+" encoder."));
		
			StegoEncoderAlgorithmHyperlink->SetLabel("More information about "+encoderName);
		}
	}
	
	void StegoEncoderWizardPage::OnStegoEncoderAlgorithmHyperlinkClick (wxHyperlinkEvent &event)
	{
		encoderName = "stego"+GetEncoderAlgorithm().Lower();
		Gui->OpenHomepageLink (this, encoderName);
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
	
	void StegoEncoderWizardPage::ConfigureStegoStorage(const std::unique_ptr<stego_disk::StegoStorage> &stego_storage){
		using namespace stego_disk;
		encoderName = GetEncoderAlgorithm();
		EncoderFactory::EncoderType encType = EncoderFactory::GetEncoderType(encoderName.ToStdString());
		stego_storage->Configure(encType, PermutationFactory::GetDefaultPermutationType(), PermutationFactory::GetDefaultPermutationType());
		
		SetStegoConfigStatus(_("Stego is configured with "+encoderName));
	}
	
	void StegoEncoderWizardPage::OnStegoRadioClicked_Manual(wxCommandEvent& event) {
		StegoEncoderAlgorithmChoice->Enable(true);
		StegoEncoderAlgorithmHyperlink->Enable(true);
		FilePathComboBox->Enable(false);
		SelectFileButton->Enable(false);
	}
	
	void StegoEncoderWizardPage::OnStegoRadioClicked_File(wxCommandEvent& event) {
		StegoEncoderAlgorithmChoice->Enable(false);
		StegoEncoderAlgorithmHyperlink->Enable(false);
		FilePathComboBox->Enable(true);
		SelectFileButton->Enable(true);
	    SetStegoConfigStatus("Specify a file path to StegoParams configuration file.");
	}
}
