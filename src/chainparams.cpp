// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.

        pchMessageStart[0] = 0x53;
        pchMessageStart[1] = 0x07;
        pchMessageStart[2] = 0x19;
        pchMessageStart[3] = 0x6a;

        vAlertPubKey = ParseHex("04d65960d060168c6ad6efd2f8cf7bd146ca0f3c9fe070e70f7104729b7abd2fcc25a76b4ceac500e5bd5a105f541be0347cd3294139018294f339431bd5f10d72");

        nDefaultPort = 16007;
        nRPCPort = 16008;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.

        //CBlock(hash=0000000102617cecd8aeba57d393e295389b83ff81f223898240282757ad7cdf, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=f43005788130cec245b86cc0a05c01769832ddbaf7fce43b526870d547e14594, nTime=1433624400, nBits=1f00ffff, nNonce=1527384, vtx=1, vchBlockSig=)
        //Coinbase(hash=f43005788130cec245b86cc0a05c01769832ddbaf7fce43b526870d547e14594, nTime=1433624400, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        //  CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a194d656e732073616e6120696e20636f72706f72652073616e6f)
        //  CTxOut(empty)
        //vMerkleTree:  f43005788130cec245b86cc0a05c01769832ddbaf7fce43b526870d547e14594

        const char* pszTimestamp = "Mens sana in corpore sano";
        CTransaction txNew;
        txNew.nTime = 1433624400;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1433624400;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 1527384;


        hashGenesisBlock = uint256("0x0000000102617cecd8aeba57d393e295389b83ff81f223898240282757ad7cdf");

        if (false && (genesis.GetHash() != hashGenesisBlock))
        {
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256()>>10;
            while (genesis.GetHash() > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time");
                    ++genesis.nTime;
                }
            }
            cout << "genesis: \n" << genesis.ToString() << endl;
            cout << "genesis.GetHash(): " << genesis.GetHash().ToString() << endl;
            cout << "genesis.hashMerkleRoot: " << genesis.hashMerkleRoot.ToString() << endl;
            cout << "genesis.nTime: " << genesis.nTime << endl;
            cout << "genesis.nNonce: " << genesis.nNonce << endl;
        }

        hashGenesisBlock = genesis.GetHash(); 

        assert(hashGenesisBlock == uint256("0x0000000102617cecd8aeba57d393e295389b83ff81f223898240282757ad7cdf"));
        assert(genesis.hashMerkleRoot == uint256("0xf43005788130cec245b86cc0a05c01769832ddbaf7fce43b526870d547e14594"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(55);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(97);
        base58Prefixes[SECRET_KEY] =     list_of(139);

        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nTargetSpacing = 30; // seconds

        nLastPOWBlock  = 10080; 
        nInstaMinePoWReward = 0 * COIN;
        nInstaMineLastBlock = 1440;
        nRegularPoWReward = 10000 * COIN; 

        nFirstPoSBlock = nLastPOWBlock - 380;
        nCoinbaseMaturity = 200;
        nLaunchTime = txNew.nTime;
        nStakeMinAge = 2 * 60 * 60;
        nModifierInterval = 1 * 60;
        nPoSCoinReward = 15; // percents
        nAdvisablePoSTxOut = 10000 * COIN;

        nMasternodeFixReward = 50 * COIN;
        nMasternodeProportionalReward = 20; // percents
        nMasternodeValue = 50000 * COIN;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.

        pchMessageStart[0] = 0x53;
        pchMessageStart[1] = 0x07;
        pchMessageStart[2] = 0x19;
        pchMessageStart[3] = 0x6d;

        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

        vAlertPubKey = ParseHex("04d65960d060168c6ad6efd2f8cf7bd146ca0f3c9fe070e70f7104729b7abd2fcc25a76b4ceac500e5bd5a105f541be0347cd3294139018294f339431bd5f10d72");

        nDefaultPort = 25007;
        nRPCPort = 25008;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 124128; //97968;

        hashGenesisBlock = uint256("0x00006dbe104010a3f14bf569d57c795fd4ad4609566ee005d56bae8f91495225");

        if (false && (genesis.GetHash() != hashGenesisBlock))
        {
            uint256 hashTarget = CBigNum().SetCompact(genesis.nBits).getuint256();
            while (genesis.GetHash() > hashTarget)
            {
                ++genesis.nNonce;
                if (genesis.nNonce == 0)
                {
                    printf("NONCE WRAPPED, incrementing time");
                    ++genesis.nTime;
                }
            }
            cout << "genesis: \n" << genesis.ToString() << endl;
            cout << "genesis.GetHash(): " << genesis.GetHash().ToString() << endl;
            cout << "genesis.hashMerkleRoot: " << genesis.hashMerkleRoot.ToString() << endl;
            cout << "genesis.nTime: " << genesis.nTime << endl;
            cout << "genesis.nNonce: " << genesis.nNonce << endl;
        }

        hashGenesisBlock = genesis.GetHash(); 
        assert(hashGenesisBlock == uint256("0x00006dbe104010a3f14bf569d57c795fd4ad4609566ee005d56bae8f91495225"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(117);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(164);
        base58Prefixes[SECRET_KEY]     = list_of(219);

        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nTargetSpacing = 10; // seconds

        nLastPOWBlock = 0x7fffffff;
        nInstaMinePoWReward = 0 * COIN;
        nInstaMineLastBlock = 1440;
        nRegularPoWReward = 10000 * COIN;

        nFirstPoSBlock = 7000;
        nCoinbaseMaturity = 200;
        nLaunchTime = 1433538000;
        nStakeMinAge = 1 * 60 * 60;
        nModifierInterval = 1 * 60;
        nPoSCoinReward = 15; // percents
        nAdvisablePoSTxOut = 10000 * COIN;

        nMasternodeFixReward = 50 * COIN;
        nMasternodeProportionalReward = 20; // percents
        nMasternodeValue = 50000 * COIN;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
