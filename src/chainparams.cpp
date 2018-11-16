// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017-2018 The Solaris developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include "chainparams.h"
#include "libzerocoin/Params.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"
#include <assert.h>
#include <boost/assign/list_of.hpp>
using namespace std;
using namespace boost::assign;
struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};
#include "chainparamsseeds.h"
/**
 * Main network
 */
//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}
//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of(0, uint256("0x00000c393bf1eaf9757be560092cc08a7b1ff0345e874b12521522e27862d7d7"))(2, uint256("0x00000310d966793ec3dd080a97b10afa0c848432c01b4053d2c6f206e1449e28"))(1479, uint256("0x00000000071b53f74e2f55ffa657cf1fc39807fb584e797ed0c6b22a4527d51c"))(5000, uint256("0x0000000002afc607345f345261bf9713c7a9cf8d50191cb338250bd4be0090b5"))(10000, uint256("0x000000000a43a6d2b09f1dbf4ea454b639838fb43686158e131d8b7a36777ca6"))(20000, uint256("0x0000000000e1a4f0659738de768c662164a20f11ca16c77dde422ee2d7369a80"))(30000, uint256("0x00000000040ac4aa7fda2d6fdd2745c788469b482eec8da79842e88bbbfc70c3"))(40000, uint256("0x0000000003265c4aded591f0b648b626abf0e4316295b6baeeadbb6c744f768e"))(50000, uint256("0x00000000052c4943642d41377f0968650871a5351c896a4cfe74e41edd2adf28"))(60000, uint256("0x00000000016a565d7d8b0c96138a9d6873510fece3beffd5295ea517ce4e6b8d"))(70000, uint256("0x00000000039673e6ee9944479068800c78f479dfb6b5d23d748d542af073440d"))(80000, uint256("0x0000000008dacfe17e44c93490c36c4d365fb6309f614c05bfa9952e9c08765f"))(89319, uint256("0x00000000031005c122f47eef1495a44221632fc7cc94b6b5ff68bc7da826c012"))(95771, uint256("0x00000000021cef5896d94a2d87d928d8fdf943a8d260386471e06b03c635acc6"))(104581, uint256("0x0000000001040e54fab7cb94317cade9461c6500c77a492ba1afd4d04949861b"))(127770, uint256("0x000000000053c7733ed070490012321680e21557bb309ebc0e52265326ffbd0d"))(130116, uint256("0x000000000059038c0121e8c503ba86ca6233b25f0ab1c4836be94d5e1bc79db9"))(152989, uint256("0x0000000000a34969026f2d3e05aa2e8464581107530d8c40ea353dc4244d3161"))(212169, uint256("0x00000000005f7efd88cc09dd9de600150868a75e27a4cb363801e79e5dda4d6d"))(233743, uint256("0x00000000005c3dd73f74c2dc59573c040851a47d4d0a51fa627b120ddf65fab7"))(259681, uint256("0x39d56c95f55f6252d5f8b476cfda56a7fff68b6db4bef208ec1700da5fca1e2a"))(260856, uint256("0x57149f1261d43c4129c3dafa8562d32b85d51753ff499061af983da5331853c7"));


static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1524057891, // * UNIX timestamp of last checkpoint block
    323011,     // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    5760        // * estimated number of transactions per day after checkpoint
};
static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x00000e535452eadc834ce63d0288ee1aa9e82ac97cfc5acad97d9d0abe63305a"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1538383362,
    0,
    1000};
static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}
class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x02;
        pchMessageStart[1] = 0x21;
        pchMessageStart[2] = 0x01;
        pchMessageStart[3] = 0xa1;
        vAlertPubKey = ParseHex("045da9271f5d9df405d9e83c7c7e62e9c831cc85c51ffaa6b515c4f9c845dec4bf256460003f26ba9d394a17cb57e6759fe231eca75b801c20bccd19cbe4b7942d");
        nDefaultPort = 60020;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Solaris starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Solaris: 1 minute
        nTargetSpacing = 1 * 60;  // Solaris: 1 minute
        nMaturity = 101;
        nMaxMoneyOut = 10000000000 * COIN;
        /** Height or Time Based Activations **/
        nLastPOWBlock = 259200;
        nModifierUpdateBlock = 1;

        nBlockEnforceSerialRange = 1;    //Enforce serial range starting this block
        nZerocoinStartTime = 1523891665; // Monday, April 16, 2018 5:14:25 PM GMT+02:00 DST
        nZerocoinStartHeight = 259300;

        const char* pszTimestamp = "Solaris 30-09-2017";

        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);

        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("045da9271f5d9df405d9e83c7c7e62e9c831cc85c51ffaa6b515c4f9c845dec4bf256460003f26ba9d394a17cb57e6759fe231eca75b801c20bccd19cbe4b7942d") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1506779239;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 500317;
        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x00000c393bf1eaf9757be560092cc08a7b1ff0345e874b12521522e27862d7d7"));
        assert(genesis.hashMerkleRoot == uint256("0xa84934befc603b6dc91cd53895bf45cd056b4e7a9562067d7608b94e8704815d"));

        vSeeds.push_back(CDNSSeedData("solarisnode.dyndns.org", "solarisnode.dyndns.org"));
        vSeeds.push_back(CDNSSeedData("solarisnode1.dyndns.org", "solarisnode1.dyndns.org"));
        vSeeds.push_back(CDNSSeedData("solarisnode2.dyndns.org", "solarisnode2.dyndns.org"));
        vSeeds.push_back(CDNSSeedData("solarisnode3.dyndns.org", "solarisnode3.dyndns.org"));
        vSeeds.push_back(CDNSSeedData("solarisnode4.dyndns.org", "solarisnode4.dyndns.org"));
        vSeeds.push_back(CDNSSeedData("solarisnode5.dyndns.org", "solarisnode5.dyndns.org"));
        vSeeds.push_back(CDNSSeedData("solarisnode6.dyndns.org", "solarisnode6.dyndns.org"));

        vSeeds.push_back(CDNSSeedData("node1.solariscoin.com", "node1.solariscoin.com"));
        vSeeds.push_back(CDNSSeedData("node2.solariscoin.com", "node2.solariscoin.com"));
        vSeeds.push_back(CDNSSeedData("node3.solariscoin.com", "node3.solariscoin.com"));
        vSeeds.push_back(CDNSSeedData("node4.solariscoin.com", "node4.solariscoin.com"));
        vSeeds.push_back(CDNSSeedData("node5.solariscoin.com", "node5.solariscoin.com"));
        vSeeds.push_back(CDNSSeedData("node6.solariscoin.com", "node6.solariscoin.com"));


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 63);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 13);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is 'TBD'
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();
        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;
        nPoolMaxTransactions = 3;
        strSporkKey = "045da9271f5d9df405d9e83c7c7e62e9c831cc85c51ffaa6b515c4f9c845dec4bf256460003f26ba9d394a17cb57e6759fe231eca75b801c20bccd19cbe4b7942d";

        strObfuscationPoolDummyAddress = "Sg3aLcSeLqbpEsVgoXtDFrpDYDfAsf1qxv";
        nStartMasternodePayments = 1403728576; //Wed, 25 Jun 2014 20:36:16 GMT

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
                          "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
                          "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
                          "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
                          "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
                          "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT;       //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20;      //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 2;
        nDefaultSecurityLevel = 100;   //full security level for accumulators
        nZerocoinHeaderVersion = 4;    //Block headers must be this version once zerocoin is active
        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;
/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x43;
        pchMessageStart[1] = 0x73;
        pchMessageStart[2] = 0x63;
        pchMessageStart[3] = 0xb3;
        vAlertPubKey = ParseHex("045da9271f5d9df405d9e83c7c7e62e9c831cc85c51ffaa6b515c4f9c845dec4bf256460003f26ba9d394a17cb57e6759fe231eca75b801c20bccd19cbe4b7942d");
        nDefaultPort = 51474;
        nMinerThreads = 0;
        nLastPOWBlock = 1000000;
        nMaturity = 2;
        nMasternodeCountDrift = 4;
        nBlockEnforceSerialRange = 1000001;
        nZerocoinStartTime = 1633077761;
        nZerocoinStartHeight = 1000005;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.

        genesis.nTime = 1538383362;
        genesis.nNonce = 262899;
        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x00000e535452eadc834ce63d0288ee1aa9e82ac97cfc5acad97d9d0abe63305a"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("testnet-solarisnode1.dyndns.org", "testnet-solarisnode1.dyndns.org"));
        vSeeds.push_back(CDNSSeedData("testnet-solarisnode2.dyndns.org", "testnet-solarisnode2.dyndns.org"));
        vSeeds.push_back(CDNSSeedData("testnet-solarisnode3.dyndns.org", "testnet-solarisnode3.dyndns.org"));
        vSeeds.push_back(CDNSSeedData("testnet-solarisnode4.dyndns.org", "testnet-solarisnode4.dyndns.org"));
        vSeeds.push_back(CDNSSeedData("testnet-solarisnode5.dyndns.org", "testnet-solarisnode5.dyndns.org"));
        vSeeds.push_back(CDNSSeedData("testnet-solarisnode6.dyndns.org", "testnet-solarisnode6.dyndns.org"));

        vSeeds.push_back(CDNSSeedData("testnet-node1.solariscoin.com", "testnet-node1.solariscoin.com"));
        vSeeds.push_back(CDNSSeedData("testnet-node2.solariscoin.com", "testnet-node2.solariscoin.com"));
        vSeeds.push_back(CDNSSeedData("testnet-node3.solariscoin.com", "testnet-node3.solariscoin.com"));
        vSeeds.push_back(CDNSSeedData("testnet-node4.solariscoin.com", "testnet-node4.solariscoin.com"));
        vSeeds.push_back(CDNSSeedData("testnet-node5.solariscoin.com", "testnet-node5.solariscoin.com"));
        vSeeds.push_back(CDNSSeedData("testnet-node6.solariscoin.com", "testnet-node6.solariscoin.com"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 22); // Testnet solaris addresses start with '9' or 'A'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19); // Testnet solaris script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);    // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet solaris BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet solaris BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet solaris BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();
        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));
        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;
        nPoolMaxTransactions = 2;
        strSporkKey = "045da9271f5d9df405d9e83c7c7e62e9c831cc85c51ffaa6b515c4f9c845dec4bf256460003f26ba9d394a17cb57e6759fe231eca75b801c20bccd19cbe4b7942d";
        strObfuscationPoolDummyAddress = "9zKPUFyz9yuL9HtTheLeMZn7YkBf5mmDEh";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
        nBudget_Fee_Confirmations = 3;         // Number of confirmations for the finalization fee. We have to make this very short
                                               // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;
/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nSubsidyHalvingInterval = 150;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Solaris: 1 day
        nTargetSpacing = 1 * 60;        // Solaris: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1454124731;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 12345;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 51476;
        //assert(hashGenesisBlock == uint256("0x4f023a2120d9127b21bbad01724fdb79b519f593f2a85b60d3d79160ec5f29df"));
        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.
        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;
/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.
        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }
    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}
CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}
void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;
    SelectParams(network);
    return true;
}