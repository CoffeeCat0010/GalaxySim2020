#pragma once
#include "Corepch.h"
#include <QWidget>
#include <QTimer>
#include <QPointer>
#include "ui_SimulationProgress.h"
#include "Compute/Simulations/NBodySim.h"

namespace Graphics{
	class SimulationProgress : public QWidget, public Ui::SimulationProgress
	{
		Q_OBJECT
	
	private:
		std::weak_ptr<Compute::NBodySim> m_sim;
		QPointer<QTimer> m_timer;
		int32_t m_numTimeSteps;
	
	public:
		SimulationProgress(std::weak_ptr<Compute::NBodySim> sim, QWidget *parent = Q_NULLPTR);
		~SimulationProgress();
	
	private:
		void updateProgress ();
	};
}
