// =================================================================================
// Thread State
// =================================================================================
enum eScriptThreadState
{
	THREAD_STATE_IDLE,
	THREAD_STATE_RUNNING,
	THREAD_STATE_KILLED,
	THREAD_STATE_UNKNOWN_1,
	THREAD_STATE_UNKNOWN_2
};

// =================================================================================
// Native Call Context
// =================================================================================
struct ScriptNativeCallContext
{
	DWORD64 m_pReturn;
	uint32_t m_iArgCount;
	DWORD64 m_pArguments;

	DWORD64 GetArgument(int iIndex);
	int GetNumArguments();

	DWORD64 SetResult(int iIndex, DWORD64 pValue);
	DWORD64 GetResult(int iIndex);
};

// =================================================================================
// Thread Context
// =================================================================================
struct ScriptThreadContext
{
	uint32_t uiThreadID; // 0x4
	uint32_t uiScriptHash; // 0x8
	eScriptThreadState eState; // 0x12
	uint32_t uiIP; // 0x10
	uint32_t uiFrameSP; // 0x14
	uint32_t Timer[3]; // 0x18
	uint32_t _unknown_1; // 0x1C
	uint32_t _unknown_2; // 0x20
	BYTE _shit[48]; // 0x2C - 0x5C
	uint32_t _unknown_3; // 0x60
	BYTE _shit2[68]; // 0xA4 (168)
};

// =================================================================================
// ScriptThread
// =================================================================================
class ScriptThread
{
public:
	ScriptThreadContext m_pContext;

	virtual ~ScriptThread() {};
	virtual eScriptThreadState Reset(uint32_t hash, void* pArgs, uint32_t iArgumentsCount) = 0;
	virtual eScriptThreadState Run(uint32_t iNumber) = 0;
	virtual eScriptThreadState Tick(uint32_t iNumber) = 0;
	virtual void Kill() = 0;

	ScriptThreadContext* GetContext() { return &m_pContext; }
};