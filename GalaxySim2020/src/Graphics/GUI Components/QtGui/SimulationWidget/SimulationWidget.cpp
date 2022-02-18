#include "Corepch.h"
#include "SimulationWidget.h"
namespace QUI{
	SimulationWidget::SimulationWidget(std::shared_ptr<Compute::Context> con, std::shared_ptr<Compute::Device> device, QWidget *parent)
		: QWidget(parent), p_con(con), p_device(device), p_validator(new QIntValidator(0, INT_MAX, this))
	{
		setupUi(this);
		timeStepsLine->setValidator(p_validator);
	}
	
	SimulationWidget::~SimulationWidget()
	{
		if(p_grid != nullptr)
			delete p_grid;
	}
	void SimulationWidget::onSaveAsClicked ()
	{
		QString path = QFileDialog::getSaveFileName (this, "Save As", "./Simulations", ".STAR");
		FilePath->setText(path + ".STAR");
	}

	//void SimulationWidget::onRunSimulationClicked ()
	//{

	//	uint32_t timeSteps;
	//	//Validation not necessary here since QIntValidator added at construction
	//	timeSteps = timeStepsLine->text().toInt(nullptr, 10);
	//
	//
	///* Start Temp Code */
	//	int numStars = 49152;
	//	Physics::Galaxy galaxy1 (numStars / 2, cl_float3{ 0.0f, -3000.0f, -5000.0f }, glm::vec3 (0.0f, 0.0f, 0.0f), glm::vec3 (0.0f, 5.0f, 0.0f), 2000.f, 150000000.f);
	//	Physics::Galaxy galaxy2 (numStars / 2, cl_float3{ 0.0f,  3000.0f, -5000.0f }, glm::vec3 (0.0f, 0.5f, 0.0f), glm::vec3 (5.0f, -5.0f, 0.0f), 2000.f, 150000000.f);
	//	
	//	std::vector<cl_float3> starPos;
	//	std::vector<cl_float3> starVel;
	//	std::vector<float> starMasses;

	//	starPos.insert (starPos.begin (), galaxy1.getStarPos ().begin (), galaxy1.getStarPos ().end ());
	//	starPos.insert (starPos.begin (), galaxy2.getStarPos ().begin (), galaxy2.getStarPos ().end ());
	//	starVel.insert (starVel.begin (), galaxy1.getStarVelocities ().begin (), galaxy1.getStarVelocities ().end ());
	//	starVel.insert (starVel.begin (), galaxy2.getStarVelocities ().begin (), galaxy2.getStarVelocities ().end ());
	//	starMasses.insert (starMasses.begin (), galaxy1.getStarMasses ().begin (), galaxy1.getStarMasses ().end ());
	//	starMasses.insert (starMasses.begin (), galaxy2.getStarMasses ().begin (), galaxy2.getStarMasses ().end ());

	//	/* End Temp Code*/
	//	QVBoxLayout* scrollBoxLayout = qobject_cast<QVBoxLayout*>(scrollAreaWidgetContents->layout ());

	//	if ( !p_progress.isNull () )
	//	{
	//		p_progress->hide();
	//		scrollBoxLayout->removeWidget(p_progress);
	//	}
	//	p_sim = std::make_shared<Compute::NBodySim>(numStars, timeSteps, FilePath->text().toStdString(),
	//																							starPos, starVel, starMasses, p_con, p_device);
	//	p_sim->run();
	//	p_progress = QPointer<SimulationProgress>(new SimulationProgress(p_sim, this));
	//	scrollBoxLayout->addWidget(p_progress);
	//	p_progress->show();
	//}

	void SimulationWidget::onRunSimulationClicked ()
	{

		uint32_t timeSteps;
		//Validation not necessary here since QIntValidator added at construction
		timeSteps = timeStepsLine->text ().toInt (nullptr, 10);


		/* Start Temp Code */
		int numStars = 49152/ 2;
		Physics::Galaxy galaxy1 (numStars , cl_float3{ 5000.0f, 3000.0f, 3000.0f }, glm::vec3 (0.0f, 0.0f, 0.0f), glm::vec3 (0.0f, 0.0f, 0.0f), 2000.f, 150000000.f);
		//Physics::Galaxy galaxy2 (numStars/2 , cl_float3 {5000.0f, 7000.0f, 3000.0f }, glm::vec3 (0.0f, 0.5f, 0.0f), glm::vec3 (0.0f, 0.0f, 0.0f), 2000.f, 150000000.f);
		int gridCellsPerDim = 256;
		float spatialSize = 15000.0; //parsecs
		std::vector<Compute::GravMass> masses;
		for ( int i = 0; i < galaxy1.getStarPos ().size (); ++i )
		{
			masses.push_back({Util::cl_float3ToVec3f (galaxy1.getStarPos ().at (i)),
												Util::cl_float3ToVec3f (galaxy1.getStarVelocities ().at (i)),
												galaxy1.getStarMasses ().at (i) });
		}
		/*for ( int i = 0; i < galaxy2.getStarPos ().size (); ++i )
		{
			masses.push_back ({ Util::cl_float3ToVec3f (galaxy2.getStarPos ().at (i)),
												Util::cl_float3ToVec3f (galaxy2.getStarVelocities ().at (i)),
												galaxy2.getStarMasses ().at (i) });
		}*/
		/*for ( int i = 0; i < numStars; ++i )
		{
			float x = (float)(rand()%5000 + 2000);
			float y = (float)(rand()%5000 + 2000);
			float z = (float)(rand()%5000 + 1000);
		
			masses.push_back ({{x, y, z },
												{0.f, 0.f, 0.f},
												5.0f});
		}*/
		//
		std::vector<Compute::GravMass> darkMasses = std::vector<Compute::GravMass>();
		p_grid = new Compute::SpatialGrid(spatialSize/gridCellsPerDim, gridCellsPerDim,
																											masses, darkMasses);
		

		/* End Temp Code*/
		QVBoxLayout* scrollBoxLayout = qobject_cast<QVBoxLayout*>(scrollAreaWidgetContents->layout ());

		if ( !p_progress.isNull () )
		{
			p_progress->hide ();
			scrollBoxLayout->removeWidget (p_progress);
		}

		float timeStepLength = 75000 * 3.154e+07; // 75,000 years in seconds
		p_sim = std::make_shared<Compute::NBodySimPM> (numStars, timeStepLength, timeSteps,  FilePath->text ().toStdString (),
																								p_grid, p_con, p_device);
		p_sim->run ();
		p_progress = QPointer<SimulationProgress> (new SimulationProgress (p_sim, this));
		scrollBoxLayout->addWidget (p_progress);
		p_progress->show ();
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