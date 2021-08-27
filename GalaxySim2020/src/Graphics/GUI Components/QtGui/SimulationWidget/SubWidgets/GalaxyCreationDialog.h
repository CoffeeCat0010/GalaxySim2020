#pragma once
#include "Corepch.h"
#include <QDialog>
#include <QIntValidator>
#include "ui_GalaxyCreationDialog.h"
#include "Generation/GalaxyParams.h"
#include "Utility/Qt/Validators/uint64Validator.h"
namespace Graphics{
	class GalaxyCreationDialog : public QDialog, public Ui::GalaxyCreationDialog
	{
		Q_OBJECT
	template<typename T>
	using u_ptr = std::unique_ptr<T>;
	public:
		GalaxyCreationDialog(QWidget *parent = Q_NULLPTR);
		~GalaxyCreationDialog();

		//Start Getters
		inline Physics::GalaxyParams getGalaxyParams() { return m_galaxy; }
	private slots:
		void accept () override;

	private: //Member Variables
		Physics::GalaxyParams m_galaxy;
		Util::uint64Validator m_numStarValidator;

		QDoubleValidator m_posInputValidator;
		QDoubleValidator m_centMassInputValidator;
		QDoubleValidator m_galDiameterValidator;
	};
}
