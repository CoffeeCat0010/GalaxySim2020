#include "Corepch.h"
#include "SimulationProgress.h"
namespace QUI{
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
		m_Etimer.start();
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
		if ( timeStepsDone == m_numTimeSteps )
		{
			float timeElapsed = (float)(m_Etimer.elapsed () / 1000);
			ProgressInfoLabel->setText (QString::number (timeStepsDone) + " of " + QString::number (m_numTimeSteps) + " done in\n " +
																	QString::number (timeElapsed) + " seconds!");
			disconnect (m_timer, &QTimer::timeout, this, &SimulationProgress::updateProgress);
		}
		else 
		{
		ProgressInfoLabel->setText(QString::number(timeStepsDone) + " of " + QString::number(m_numTimeSteps) + " done!" );
		m_timer->start(16);
	  }
	}
}