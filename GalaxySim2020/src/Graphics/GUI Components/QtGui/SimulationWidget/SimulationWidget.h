#pragma once
#include "Corepch.h"
#include <QWidget>
#include <QPointer>
#include <QFileDialog>
#include "ui_SimulationWidget.h"
#include "SimulationProgress.h"
#include "Compute/Simulations/NBodySim.h"
#include "Generation/Galaxy.h"
#include "Compute/CLprim/CLPrim.h"
#include "CL/cl.hpp"
namespace Graphics{
	class SimulationWidget : public QWidget, public Ui::SimulationWidget
	{
		Q_OBJECT
		
		std::shared_ptr<Compute::Context> p_con;
		std::shared_ptr<Compute::Device> p_device;
		std::shared_ptr<Compute::NBodySim> p_sim;
		
		
		QPointer<SimulationProgress> p_progress;

		
	public:
		SimulationWidget(std::shared_ptr<Compute::Context> con,  std::shared_ptr<Compute::Device> device, QWidget *parent = Q_NULLPTR);
		~SimulationWidget();
		
		// Setters
		inline void setContext (std::shared_ptr<Compute::Context> con) { p_con = con; }
		inline void setDevice (std::shared_ptr<Compute::Device> device) {p_device = device;}
	public slots:
		void onContextUpdated(std::shared_ptr<Compute::Context> con);
		void onDeviceUpdated(std::shared_ptr<Compute::Device> device);
	private slots:
		void onSaveAsClicked();
		void onRunSimulationClicked();
	};
}