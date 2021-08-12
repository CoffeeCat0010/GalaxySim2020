#include "Corepch.h"
#include "SimulationProgress.h"
namespace Graphics{
	SimulationProgress::SimulationProgress(std::weak_ptr<Compute::NBodySim> sim, QWidget *parent)
		: QWidget(parent), m_sim(sim)
	{
		setupUi(this);
		m_timer = QPointer<QTimer>(new QTimer(this));
		connect(m_timer, &QTimer::timeout, this, &SimulationProgress::updateProgress);
		std::shared_ptr<Compute::NBodySim> l_sim = m_sim.lock ();
		m_numTimeSteps = l_sim->getNumTimesteps ();
		progressBar->setRange(0, m_numTimeSteps);
		m_timer->start(16);
	}
	
	SimulationProgress::~SimulationProgress()
	{
	}
	void SimulationProgress::updateProgress ()
	{
		if(m_sim.expired())
			return;
		std::shared_ptr<Compute::NBodySim> l_sim = m_sim.lock();
		int32_t timeStepsDone = l_sim->getTimestepsDone ();
		progressBar->setValue(timeStepsDone);
		ProgressInfoLabel->setText(QString::number(timeStepsDone) + " of " + QString::number(m_numTimeSteps) + " done!" );
		m_timer->start(16);
	}
}