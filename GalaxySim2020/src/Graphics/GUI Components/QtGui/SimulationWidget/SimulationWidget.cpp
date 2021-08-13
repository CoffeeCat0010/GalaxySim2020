#include "Corepch.h"
#include "SimulationWidget.h"
namespace Graphics{
	SimulationWidget::SimulationWidget(std::shared_ptr<Compute::Context> con, std::shared_ptr<Compute::Device> device, QWidget *parent)
		: QWidget(parent), p_con(con), p_device(device)
	{
		setupUi(this);
	}
	
	SimulationWidget::~SimulationWidget()
	{
		
	}
	void SimulationWidget::onSaveAsClicked ()
	{
		QString path = QFileDialog::getSaveFileName (this, "Save As", "./Simulations", ".STAR");
		FilePath->setText(path + ".STAR");
	}

	void SimulationWidget::onRunSimulationClicked ()
	{

		uint32_t timeSteps;
		bool validTimeSteps;
		timeSteps = timeStepsLine->text().toInt(&validTimeSteps, 10);
		if ( !validTimeSteps )
		{
			//TODO: Add Dialog to explain what happened
			return;
		}
	
	
	/* Start Temp Code */
		int numStars = 8192;
		Physics::Galaxy galaxy1 (numStars / 2, cl_float3{ 0.0f, 6000.0f, -3000.0f }, glm::vec3 (0.0f, 0.0f, 0.0f), glm::vec3 (0.0f, 5.0f, 0.0f), 2000.f, 150000000.f);
		Physics::Galaxy galaxy2 (numStars / 2, cl_float3{ 0.0f, 3000.0f, -3000.0f }, glm::vec3 (0.0f, 0.5f, 0.0f), glm::vec3 (5.0f, -5.0f, 0.0f), 2000.f, 150000000.f);
		
		std::vector<cl_float3> starPos;
		std::vector<cl_float3> starVel;
		std::vector<float> starMasses;

		starPos.insert (starPos.begin (), galaxy1.getStarPos ().begin (), galaxy1.getStarPos ().end ());
		starPos.insert (starPos.begin (), galaxy2.getStarPos ().begin (), galaxy2.getStarPos ().end ());
		starVel.insert (starVel.begin (), galaxy1.getStarVelocities ().begin (), galaxy1.getStarVelocities ().end ());
		starVel.insert (starVel.begin (), galaxy2.getStarVelocities ().begin (), galaxy2.getStarVelocities ().end ());
		starMasses.insert (starMasses.begin (), galaxy1.getStarMasses ().begin (), galaxy1.getStarMasses ().end ());
		starMasses.insert (starMasses.begin (), galaxy2.getStarMasses ().begin (), galaxy2.getStarMasses ().end ());

		/* End Temp Code*/

		p_sim = std::make_shared<Compute::NBodySim>(numStars, timeSteps, FilePath->text().toStdString(),
																								starPos, starVel, starMasses, p_con, p_device);
		p_sim->run();
		p_progress = QPointer<SimulationProgress>(new SimulationProgress(p_sim, this));
		scrollLayout->addWidget(p_progress);
		p_progress->show();
	}

	void SimulationWidget::onContextUpdated (std::shared_ptr<Compute::Context> con)
	{
		setContext(con);
	}

	void SimulationWidget::onDeviceUpdated (std::shared_ptr<Compute::Device> device)
	{
		setDevice(device);
	}
	
}