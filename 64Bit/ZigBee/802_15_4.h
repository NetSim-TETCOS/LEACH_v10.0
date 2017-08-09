/************************************************************************************
* Copyright (C) 2013                                                                *
* TETCOS, Bangalore. India                                                          *
*                                                                                   *
* Tetcos owns the intellectual property rights in the Product and its content.      *
* The copying, redistribution, reselling or publication of any or all of the        *
* Product or its content without express prior written consent of Tetcos is         *
* prohibited. Ownership and / or any other right relating to the software and all   *
* intellectual property rights therein shall remain at all times with Tetcos.       *
*                                                                                   *
* Author:    Shashi Kant Suman						                                *
*                                                                                   *
* ---------------------------------------------------------------------------------*/

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  *
*                                                                                        *
*	THIS FILES CONTAINS IEEE 802.15.4 DATASTUCTURE WHICH HAS VARIABLES THAT ARE PROVIDED *
*   FOR USERS. BY MAKING USE OF THESE VARIABLES THE USER CAN CREATE THEIR OWN PROJECT.   *
*	                                                                                     *    
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  */
#ifndef _NETSIM_802_15_4_H_
#define _NETSIM_802_15_4_H_
#ifdef  __cplusplus
extern "C" {
#endif

#pragma comment(lib,"PropagationModel.lib")

#define dUnitSymbolTime  ((4*1000000)/250000) //Time taken to transfer 1 symbols. Each symbol is 4 bit long.
#define WSN_PHY(devId) ((IEEE802_15_4_PHY_VAR*)DEVICE_PHYVAR(devId,1))
#define WSN_MAC(devId) ((IEEE802_15_4_MAC_VAR*)DEVICE_MACVAR(devId,1))
#define WSN_LINK_ID(nDevice_Id,nInterfaceId,nConnectedDevId,nConnectedDevPortId) fn_NetSim_Stack_GetConnectedDevice(nDevice_Id,nInterfaceId,nConnectedDevId,nConnectedDevPortId);
#define WSN_MAC_HEADER(pPacket) ((IEEE802_15_4_HEADER*)PACKET_MACPROTOCOLDATA(pPacket))
#define CHANNEL_IDLE 0
#define CHANNEL_BUSY 1

#define MAXAGENT 100
#define MAX_TTL 255
#define SOURCEPORT 45
#define DESTINATIONPORT 50
#define BATTERY 1
#define MAINLINE 2

	/* Typedef declaration of structures */
	typedef struct stru_IEEE802_15_4_Header IEEE802_15_4_HEADER;
	typedef struct stru_IEEE802_15_4_MacVar IEEE802_15_4_MAC_VAR;
	typedef struct stru_IEEE802_15_4_PhyVar IEEE802_15_4_PHY_VAR;
	typedef struct stru_IEEE802_15_4_Primitives IEEE802_15_4_PRIMITIVES;
	typedef struct stru_BeaconFrame BEACONFRAME;
	typedef struct stru_SuperFrame SUPERFRAME;
	typedef struct stru_GTS GTS;
	typedef struct stru_Agent AGENT;
	typedef struct stru_Position_2D POS_2D;
	typedef struct stru_Sensor SENSORS;
	typedef struct struChannel CHANNELS;
	typedef struct stru_SinkNodeModel SINKNODEMODEL;
	typedef struct struPower POWER;
	typedef struct stru_IEEE802_15_4_Metrics IEEE802_15_4_METRCIS;
	typedef struct stru_SensorMetrics SENSOR_METRICS;
	typedef struct stru_Powermodel POWER_MODEL;
	typedef struct stru_Metrics METRICS;
	typedef struct stru_AgentLog AGENTLOG;

	/* Typedef declaration of enumerations */
	typedef enum enum_CCAMODE CCAMODE;
	typedef enum enum_IEEE_802_15_4_ControlPacket_Type IEEE802_15_4_PACKET_TYPE;
	typedef enum enum_BeaconMode BEACON_MODE;
	typedef enum enum_IEEE802_15_4_Subevent_Type SUB_EVENT;
	typedef enum enum_MacState MAC_STATE;
	/** Enumeration for Zigbee Control packet type */
	enum enum_IEEE_802_15_4_ControlPacket_Type
	{
		BEACON_FRAME = MAC_PROTOCOL_IEEE802_15_4*100+1,
		SLEEP_FRAME,
		GTS_REQUEST,
		GTS_ACK,
		ACK_FRAME,
		GTS_ACKFRAME,
	};
	/** Enumeration for Zigbee Super frame statue */
	enum enum_SuperFrame_Status
	{
		BEACONTRANSMISSIONMODE,
		CAPMODE,
		CFPMODE,
		INACTIVEMODE,
	};

	/** Defining sub event type of IEEE 802.15.4*/
	enum enum_IEEE802_15_4_Subevent_Type
	{
		SUPERFRAME_EVENT = MAC_PROTOCOL_IEEE802_15_4*100+1,
		CARRIERSENSE_START,
		CARRIERSENSE_END,
		ACK_TIMEOUT,			
		BEACON_TRANSMISSION, 
		GOFORSLEEP,			
		BEACON_TRANSMISSION_END, 
		CAP_END,				
		CFP_END,				
		GTS_REQUESTEVENT,	
		GTS_ACKEVENT,		
		GTS_DATATRANSFER,	
		GTS_ACKTIMEOUT,		
		GTS_DATAACK,			
		ACK_EVENT,			
		CSMA_DATATRANSFER,	
		CHANGE_RX,			
		CHANGE_RXANDSENDDATA,
		UPDATE_MEDIUM,
		SENSOR_EVENT,
	};
	/** Enumeration for Zigbee CCA Mode */
	enum enum_CCAMODE
	{
		CARRIERSENSE,
		ENERGYABOVETHERESHOLD,
		CARRIERSENSE_AND_ENERGYABOVETHERESHOLD,
		CARRIERSENSE_OR_ENERGYABOVETHERESHOLD,
	};
	/** Enumeration for Beacon mode (Enable or disable) */
	enum enum_BeaconMode
	{
		BEACON_DISABLE,
		BEACON_ENABLE,
	};
	/** Enumeration for GTS mode(Enable or Disable) */
	enum enum_GTSMode
	{
		GTS_ENABLE,
		GTS_DISABLE,
	};

	/** Enumeration for MAc state */
	enum enum_MacState
	{
		IDLE,
		BACKOFF_MODE,
		CCA_MODE,
		TX_MODE,
		RX_MODE,
		OFF,
	};

	enum enum_IEEE802_15_4_isConfigured
	{
		DISABLE=0,
		ENABLE=1,
	};
	/** Enumeration for Mobility model */
	enum enum_Mobility_Model
	{
		NOMOBILITY,
		RANDOMWALK,
		RANDOMWAYPOINT,
	};

	NETSIM_ID nGlobalPANCoordinatorId;
	/** Structure for IEEE 802.15.4 */
	struct stru_IEEE802_15_4_Header
	{
		//int n_NC_ChannelId;
		int nAckRequestFlag;
		struct stru_BeaconFrame* pstruBeaconFrame;
		//struct stru_NP_GTSRequestFrame* pstruGTSRequestFrame;	
	};
	/** Data structure for GTS */
	struct stru_GTS
	{
		/// This variable is used to know the GTS Id
		int nGTSId;
		/// This variable is used to know the  SuperFrame Id
		int nSuperFrameId;
		/// Represents the superframe slot at which the GTS is to begin.
		int nStartingSlot;
		/// Represents number of contiguous slots over which the GTS is active.
		int nSlotCount;
		/// GTS Allocation status = Busy or Idle
		int nGTSAllocationStatus; 
		int nAllocatedDeviceId;
	};
	/** Data structure for Beacon frame */
	struct stru_BeaconFrame
	{
		int nBeaconId;
		int nSuperFrameId;
		int nBeaconTime;
		double dPayload;
		double dOverhead;
		double dFrameSize;
		//GTS* pstruGTSInformation;
	};

	/** Data structure for Superframe */
	struct stru_SuperFrame
	{
		int nSuperFrameId;
		int nNumberOfGTS;
		int nTimeSlotCount;
		int nSuperFrameStatus;
		double dSuperFrameStartTime;
		double dSuperFrameLength;
		double dActivePeriodLength;
		double dInactivePeriodLength;
		double dTimeSlotLength;
		double dCAPLength;
		double dCFPLength;
		double dBeaconLength;
		//	GTS* pstruGTSList[7];
		BEACONFRAME* pstruBeacon;
		struct stru_SuperFrame* pstruNextSuperFrame;
	};
	SUPERFRAME* pstruSuperFrame;
	/// Structure to store the agent details.
	struct stru_Agent
	{

		int id;
		/// Stores the agent id.
		int nAgentID;
		/// Stores the mobility model.
		int nMobilityModel;
		/// stores X-coordinate of the environment.
		double dWorkingArea_X;
		/// Stores Y-coordinate of the environment.
		double dWorkingArea_Y;
		/// Stores velocity of the agent.
		int nVelocity;
		/// Stores the pause time of the agent.
		int nPauseTime;
		POS_2D* pstruPos;
		POS_2D* pstruCurrPos;
		POS_2D* pstruTracePos;

		int config_mode;
		char* client_ip;
		NETSIM_ID sensor_id;
	};
	/** Data structure for agent position */
	struct stru_Position_2D
	{
		double dTime_sec;
		double dXPos;
		double dYPos;
		struct stru_Position_2D* pstruNextPos;
	};
	int nAgentCount;
	int nWSNFlag;
	AGENT* pstruAgent[MAXAGENT];
	bool emulated_agent_flag;
	/** Data structure for sensor*/
	struct stru_Sensor
	{
		/// Represents the time gap between two successive sensor events of a sensor.
		double dSensingInterval; //In microsec
		/// DataLogging - 1
		int nSinkNodeAction;
		/** 1- To Enable, 0- To Disable */
		int nDataLoggingFlag;	
		/// Range of the sensor.
		double dSensorRange;
		char* szFileName;
		char* szFilePath;
	};
	SENSORS** pstru_Sensor;

	/// Stores the information of MAC layer.
	struct stru_IEEE802_15_4_MacVar
	{
		MAC_STATE nNodeStatus;
		int nAckRequestFlag;
		BEACON_MODE nBeaconMode;
		/// Range = 0 - 15 ; Default = 15 
		int nMacBeaconOrder;	
		/// Range = 0 - 15 ;  Default = 15 
		int nMacSuperframeOrder;
		int nMacGTSPermit;
		/// 15.36 ms for 2.4 GHz
		double dBaseSuperFrameDuration; 
		/// Enable or Disable
		int nBatteryLifeExtension;	
		/// Range = 3 - 8 ; Default = 5 
		int nMacMaxBE;				
		///  Range = 0 - 5 ; Default = 4 
		int nMacMaxCSMABackoff;		
		/// Range = 0 - nMacMaxBE ; Default = 3     
		int nMacMinBE;				
		/// Range = 0 - 7 ;   Default = 3
		int nMacMaxFrameRetries;	
		/// 20 Symbols fixed
		int aUnitBackoffPeriod;		
		int nMinCAPLength;
		int nGTSDescPersistenceTime;

		/// POWER** pstruDevicePower;
		/// specific to simulation
		int nBackoffExponent;
		NetSim_PACKET *pstruBuffer;
		int nRetryCount;
		/// To perform CCA in Slotted CSMACA 
		int nContentionWindow; 
		int nNoOfBackOff;
		int nBeaconReceivedFlag;
		int nLastBeaconId;
		int nChannelNumber;
	};
	/// Structure to store sinknode model
	struct stru_SinkNodeModel
	{
		/// Sink node model properties
		/// DataLogging - 1
		int nSinkNodeAction;	
		/// 	1-Enable   0-Disable  
		int nDataLoggingFlag;	 


		char* szFileName;
		char* szFilePath;
	};
	SINKNODEMODEL *pstruSinkNodeModel;
	/// Stores information of physical layer.
	struct stru_IEEE802_15_4_PhyVar
	{
		double dAntennaHeight;
		double dAntennaGain;
		unsigned long int ulSeed1, ulSeed2;
		/// -85 dbm default 
		double dReceiverSensivity; 
		/// -85 -10 = -95 dbm default 
		double dEDThreshold;		 
		double dTransmitterPower_mw;
		double dTransmitterRange_m;
		/// Working Frequency Range. In MHz
		double dFrequencyBand_MHz;	
		/// Data rate in kbps
		double dDataRate_kbps;		
		/// Chip Rate in mcps
		double dChipRate_mcps;
		double dSymobleRate_kSymbolsPS;
		char* pszModulationTechnique;
		double dMinLIFSPeriod_Symbols;
		double dMinSIFSPeriod_Symbols;
			
		/// 20 symbols fixed 
		int aUnitBackoffPeriod; 
		/// 12 symbols fixed 
		int aTurnaroundTime; 
		/// 3, 7, 10, 40 
		int phySHRDDuration; 
		/// 0.4, 1.6, 2, 8
		double phySymbolsPerOctet;  
		/// CCA Mode
		CCAMODE enumCCAMode;       
		PHY_TX_STATUS nRadioState;
		double dTotalReceivedPower;
		double macAckWaitDuration;
		int nSensorFlag;
		PHY_TX_STATUS nOldState;

		double d0;
		double pl_d0;

	};
	/** Data structure for channel */
	struct struChannel
	{
		/// Stores the channel number.
		int nChannelNumber;
		/// Stores the frequency.
		double dFrequency;
		/// Stores channel(IDLE,BUSY etc) status.
		int nChannelStatus;
		/// Deviceid to which it is allocated.
		int nAllocatedDeviceId;
		/// Type of the divice to which it is allocated.
		int nAllocatedDeviceType;
		/// Count of the devices those have been assigned to the channel
		int nAssociatedDeviceCount;
		int nNoOfPacket;
	};
	CHANNELS* pstruChannelList;

	/// Structure for Power model.
	struct struPower
	{
		int nDeviceId;
		int nPowerSource; /* Battery
						  MainLine */
		int nEnergyHarvesting;
		double dRechargingCurrent_mA;
		double dInitialEnergy_mW;
		double dVoltage_V;
		double dTransmittingCurrent_mA;
		double dReceivingCurrent_mA;
		double dIdleModeCurrent_mA;
		double dSleepModeCurrent_mA;
		int nNodeStatus;	// 1 for ON, 0 for OFF
		int nNodePrevStatus;
		double dPrevChangedStateTime;
		double dRemainingPower;
		double dTransmissionModeEnergyConsumed;
		double dReceptionModeEnergyConsumed;
		double dSleepModeEnergyConsumed;
		double dIdleModeEnergyConsumed;
		bool isnometrics;
	};
	
	#ifndef _LEACH
	_declspec(dllexport) POWER** pstruDevicePower;

	//For LEACH/Data Metrics
	// Array size is 101 since maximum number of sensors is 100 and 1 for sink
	_declspec(dllexport) int Data_Packet_Sent_NWL[101] ;
	_declspec(dllexport) int Data_Packet_Received_NWL[101] ;
	_declspec(dllexport) int Data_Packet_Sent_PL[101] ;
	_declspec(dllexport) int Data_Packet_Received_PL[101] ;
	_declspec(dllexport) double Lifetime[101];

#else

	_declspec(dllimport) POWER** pstruDevicePower;

	//For LEACH/Data Metrics
	// Array size is 101 since maximum number of sensors is 100 and 1 for sink

	_declspec(dllimport) int Data_Packet_Sent_NWL[101] ;
	_declspec(dllimport) int Data_Packet_Received_NWL[10] ;
	_declspec(dllimport) int Data_Packet_Sent_PL[101] ;
	_declspec(dllimport) int Data_Packet_Received_PL[101] ;
	_declspec(dllimport) double Lifetime[101];
#endif
	// Array size is 101 since maximum number of sensors is 100 and 1 for sink
	
	
	/// Structure for IEEE 802.15.4 Metrics 
	struct stru_IEEE802_15_4_Metrics
	{
		int nPacketTransmitted;
		int nPacketReceived;
		int nAckTransmitted;
		int nAckReceived;
		int nCCAAttempt;
		int nSuccessfulCCAAttempt;
		int nFailedCCA;
		double dTotalbackofftime;
		double  dAveragebackofftime;
		int nNumberofBackoffCall;
		int nBeaconTransmitted;
		int nBeaconReceived;
		int nBeaconForwarded;
		double dBeaconTime;
		double dCAPTime;
		double dCFPTime;
	};
	/// Structure that contains information that is logged inside of agent log.
	struct stru_AgentLog
	{
		double dTime;
		int nAgentId;
		double dX;
		double dY;
		struct element* ele;
	};
	/// Structure to store the sensor metrics.
	struct stru_SensorMetrics
	{
		int nAgentSensedCount;
		int nPacketGenerated;
		AGENTLOG *pstruAgentLog;
	};
	/// Structure store the power details of sensor.
	struct stru_Powermodel
	{
		double dTotalEnergyConsumed;
		double dReceivingEnergyConsumed;
		double dTransmissionEnergyConsumed;
		double dIdleEnergyConsumed;
		double dSleepEnergyConsumed;
	};
	/// Data structure for IEEE 802.15.4 metrics which consists of sensor metrics and power model metrics also.
	struct stru_Metrics
	{
		IEEE802_15_4_METRCIS *pstruIEEE802_15_4_Metrics;
		SENSOR_METRICS *pstruSensorMetrics;
		POWER_MODEL *pstruPowerModel;
	};
	METRICS** pstruMetrics;

	PROPAGATION_HANDLE propagationHandle;
	//Propagation macro
#define GET_RX_POWER_dbm(tx, rx, time) (propagation_get_received_power_dbm(propagationHandle, tx, 1, rx, 1, time))
#define GET_RX_POWER_mw(tx,rx,time) (DBM_TO_MW(GET_RX_POWER_dbm(tx,rx,time)))


#define ZIGBEE_UNSLOTTED() fn_NetSim_Zigbee_UnslottedCSMACA(pstruMetrics,pstruDevicePower,pstruEventDetails)
#define ZIGBEE_SLOTTED() fn_NetSim_Zigbee_SlottedCSMACA(pstruSuperFrame,pstruMetrics,pstruDevicePower,pstruEventDetails)
#define ZIGBEE_AGENTMOBILITY() fn_NetSim_Zigbee_AgentMobility(pstruAgent,pstruEventDetails)
#define ZIGBEE_SENSOREVENT(nSensorLoop) fn_NetSim_Zigbee_SensorEvent(nSensorLoop,nGlobalPANCoordinatorId,pstruAgent,pstruMetrics,pstruEventDetails)
#define ZIGBEE_CHANGERADIOSTATE(nDeviceId,nOldState,nNewState) fn_NetSim_Zigbee_ChangeRadioState(nDeviceId,nOldState,nNewState,pstruDevicePower,pstruEventDetails)
#define ZIGBEE_RECEIVEDPOWER(pstruPhyVar,dDistance,dReceivedPower,nLinkID) fn_NetSim_Zigbee_CalculateReceivedPower(pstruPhyVar,dDistance,dReceivedPower,nLinkID,pstruEventDetails)
#define ZIGBEE_SHADOWLOSS(ulSeed1,ulSeed2,dShadowReceivedPower,dStandardDeviation) fn_NetSim_Zigbee_CalculateShadowLoss(ulSeed1,ulSeed2,dShadowReceivedPower,dStandardDeviation,pstruEventDetails)
#define ZIGBEE_ERRORPATHLOSS(nErrorRate,ldPacketSize,dEpsilon) fn_NetSim_Zigbee_ErrorPathloss(nErrorRate,ldPacketSize,dEpsilon,pstruEventDetails)
#define ZIGBEE_BER(dSNR,dBER,dErrorRange) fn_NetSim_Zigbee_CalculateBER(dSNR,dBER,dErrorRange,pstruEventDetails)
#define ZIGBEE_LOCATEBACKOFFBOUNDARY(dTime,dBoundaryTime,aUnitBackoffPeriod,pstruSuperFrame) fn_NetSim_Zigbee_LocateBackoffBoundary(dTime,dBoundaryTime,aUnitBackoffPeriod,pstruSuperFrame,pstruEventDetails)
#define ZIGBEE_SUPERFRAME() fn_NetSim_Zigbee_SuperFrameInitialization(&pstruSuperFrame,nGlobalPANCoordinatorId,pstruMetrics,pstruEventDetails)
#define ZIGBEE_BACKOFF(nBackoffExponent,dBackoffTime,nUnitBacoffPeriod) fn_NetSim_Zigbee_BackoffTimeCalculation(nBackoffExponent,dBackoffTime,nUnitBacoffPeriod,pstruMetrics,pstruEventDetails)
#define ZIGBEE_CHANNELFORMATION() fn_NetSim_Zigbee_ChannelFormation(&pstruChannelList,pstruEventDetails)
#define ZIGBEE_CCA(dInterferencePower,nCCA_Mode,dReceiverSensivity,dEDThreshold) fn_NetSim_Zigbee_CCA(dInterferencePower,nCCA_Mode,dReceiverSensivity,dEDThreshold,pstruMetrics,pstruEventDetails)
#define ZIGBEE_SINR(SNR,dTotalReceivedPower,dReceivedPower) fn_NetSim_Zigbee_CalculateSINR(SNR,dTotalReceivedPower,dReceivedPower,pstruEventDetails)

	/* Zigbee Function */
	int fn_NetSim_Configure_WSN_AGENT(void*, int);
	int fn_NetSim_Configure_WSN_POWER(void*, int);


	/****************** NetWorkStack DLL functions declarations *****************************************/
	/** Function for configuring Zigbee parameters*/
	_declspec(dllexport) int fn_NetSim_Zigbee_Configure(void** var);
	int fn_NetSim_Zigbee_Configure_F(void** var);
	/** Function for Intializing Zigbee protocol */
	_declspec (dllexport) int fn_NetSim_Zigbee_Init(struct stru_NetSim_Network *NETWORK_Formal,NetSim_EVENTDETAILS *pstruEventDetails_Formal,char *pszAppPath_Formal,char *pszWritePath_Formal,int nVersion_Type,void **fnPointer);
	int fn_NetSim_Zigbee_Init_F(struct stru_NetSim_Network *,NetSim_EVENTDETAILS *,char *,char *,int ,void **fnPointer);
	/** Function to run Zigbee protocol */
	_declspec (dllexport) int fn_NetSim_Zigbee_Run();

	int fn_NetSim_Zigbee_Primitive_Load();

	/// Function to free the Zigbee protocol variable and Unload the primitives
	_declspec(dllexport) int fn_NetSim_Zigbee_Finish();
	int fn_NetSim_Zigbee_Finish_F();
	/// Return the subevent name with respect to the subevent number for writting event trace
	_declspec (dllexport) char *fn_NetSim_Zigbee_Trace(int nSubEvent);
	char *fn_NetSim_Zigbee_Trace_F(int nSubEvent);
	/// Function to free the allocated memory for the Zigbee packet
	_declspec(dllexport) int fn_NetSim_Zigbee_FreePacket(NetSim_PACKET* );
	int fn_NetSim_zigbee_FreePacket_F(NetSim_PACKET* );
	/// Function to copy the Zigbee packet from source to destination
	_declspec(dllexport) int fn_NetSim_Zigbee_CopyPacket(NetSim_PACKET* ,NetSim_PACKET* );
	int fn_NetSim_Zigbee_CopyPacket_F(NetSim_PACKET* ,NetSim_PACKET* );
	/// Function to write Zigbee Metrics into Metrics.txt
	_declspec(dllexport) int fn_NetSim_Zigbee_Metrics(PMETRICSWRITER metricsWriter);
	int fn_NetSim_Zigbee_Metrics_F(PMETRICSWRITER metricsWriter);


	_declspec(dllexport) int fn_NetSim_Zigbee_PowerModel();
#define AGENTLOG_ALLOC() (AGENTLOG*)list_alloc(sizeof(AGENTLOG),offsetof(AGENTLOG,ele))


	//Backoff seed

	unsigned long ulBackoffSeed1;
	unsigned long ulBackoffSeed2;

	int fn_NetSim_Zigbee_UnslottedCSMACA(METRICS** pstruMetrics,POWER** pstruDevicePower,NetSim_EVENTDETAILS* pstruEventDetails);
	int fn_NetSim_Zigbee_SlottedCSMACA(SUPERFRAME* pstruSuperFrame,METRICS** pstruMetrics,POWER** pstruDevicePower,NetSim_EVENTDETAILS* pstruEventDetails);
	int fn_NetSim_Zigbee_AgentMobility(AGENT** pstruAgent,NetSim_EVENTDETAILS* pstruEventDetails);
	int fn_NetSim_Zigbee_SensorEvent(int nSensorLoop,NETSIM_ID nGlobalPANCoordinatorId,AGENT** pstruAgent,METRICS** pstruMetrics,NetSim_EVENTDETAILS* pstruEventDetails);
	int fn_NetSim_Zigbee_ChangeRadioState(NETSIM_ID nDeviceId, PHY_TX_STATUS nOldState, PHY_TX_STATUS nNewState,POWER** pstruDevicePower,NetSim_EVENTDETAILS* pstruEventDetails);
	int fn_NetSim_Zigbee_CalculateReceivedPower(IEEE802_15_4_PHY_VAR *pstruPhyVar, double dDistance,double* dReceivedPower, NETSIM_ID nLinkID,NetSim_EVENTDETAILS* pstruEventDetails);
	int fn_NetSim_Zigbee_CalculateShadowLoss(unsigned long* ulSeed1, unsigned long* ulSeed2, double* dShadowReceivedPower,double dStandardDeviation,NetSim_EVENTDETAILS* pstruEventDetails);
	int fn_NetSim_Zigbee_ChannelFormation(CHANNELS** pstruChannelList,NetSim_EVENTDETAILS* pstruEventDetails);
	int fn_NetSim_Zigbee_ErrorPathloss(int nErrorRate,double ldPacketSize,double dEpsilon,NetSim_EVENTDETAILS* pstruEventDetails);
	int fn_NetSim_Zigbee_CalculateBER(double dSNR, double* dBER, double* dErrorRange,NetSim_EVENTDETAILS* pstruEventDetails);
	int fn_NetSim_Zigbee_LocateBackoffBoundary(double dTime, double* dBoundaryTime, int aUnitBackoffPeriod, SUPERFRAME* pstruSuperFrame,NetSim_EVENTDETAILS* pstruEventDetails);
	int fn_NetSim_Zigbee_SuperFrameInitialization(SUPERFRAME** ppstruSuperFrame,NETSIM_ID nGlobalPANCoordinatorId,METRICS** pstruMetrics,NetSim_EVENTDETAILS* pstruEventDetails);
	int fn_NetSim_Zigbee_BackoffTimeCalculation(int nBackoffExponent,double* dBackoffTime,int nUnitBacoffPeriod,METRICS** pstruMetrics,NetSim_EVENTDETAILS* pstruEventDetails);
	int fn_NetSim_Zigbee_CCA(double dInterferencePower, CCAMODE nCCA_Mode, double dReceiverSensivity, double dEDThreshold,METRICS** pstruMetrics,NetSim_EVENTDETAILS* pstruEventDetails);
	int fn_NetSim_Zigbee_CalculateSINR(double *SNR, double dTotalReceivedPower,double dReceivedPower,NetSim_EVENTDETAILS* pstruEventDetails);

#ifdef  __cplusplus
}
#endif
#endif
