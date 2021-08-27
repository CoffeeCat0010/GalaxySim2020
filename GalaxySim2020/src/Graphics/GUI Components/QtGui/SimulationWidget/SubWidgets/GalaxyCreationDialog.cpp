#include "GalaxyCreationDialog.h"
namespace Graphics{
	GalaxyCreationDialog::GalaxyCreationDialog(QWidget *parent)
		: QDialog(parent)
	{
		setupUi(this);

		p_numStarLEdit->setValidator(&m_numStarValidator);
		p_massOfCentMassLEdit->setValidator(&m_centMassInputValidator);
		p_galDiameterLEdit->setValidator(&m_galDiameterValidator);
		p_xPosLEdit->setValidator (&m_posInputValidator);
		p_yPosLEdit->setValidator (&m_posInputValidator);
		p_zPosLEdit->setValidator (&m_posInputValidator);

	}
	
	GalaxyCreationDialog::~GalaxyCreationDialog()
	{
	}
	void GalaxyCreationDialog::accept ()
	{
		m_galaxy.pos = {p_xPosLEdit->text ().toFloat (), 
										p_yPosLEdit->text ().toFloat (), 
										p_zPosLEdit->text ().toFloat ()};
		m_galaxy.rotation = {static_cast<float>(p_xRotDSBox->value ()),
												 static_cast<float>(p_yRotDSBox->value ()),
												 static_cast<float>(p_zRotDSBox->value ())};
		m_galaxy.diameter = p_galDiameterLEdit->text().toFloat();
		m_galaxy.centerMass = p_massOfCentMassLEdit->text().toFloat();
		m_galaxy.starMass = static_cast<float>(p_starMassDSBox->value());
		m_galaxy.numStars = p_numStarLEdit->text().toInt();

		m_galaxy.hasCenterMass = p_centMassCombo->currentText() == "Yes" ? true : false;
		m_galaxy.RotInRads = false;
		emit accepted();
	}
}
