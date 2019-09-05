#import <Foundation/Foundation.h>

#define RCN_SEC_PER_MIN 60
#define RCN_MSEC_PER_SEC 1000

/// Remote Config SDK internal version that is different than
/// FIRRemoteConfigPodVersion. This is for config server to track down iOS
/// client app version. Each version can only go up to 99.
static const int kRCNMajorVersion = 1;
static const int kRCNMinorVersion = 2;
static const int kRCNPatchVersion = 10;

/// Key prefix applied to all the packages (bundle IDs) in internal metadata.
static NSString *const RCNInternalMetadataAllPackagesPrefix = @"all_packages";

/// HTTP connection default timeout in seconds.
static const NSTimeInterval RCNHTTPDefaultConnectionTimeout = 60;
/// Default duration of how long config data lasts to stay fresh.
static const NSTimeInterval RCNDefaultMinimumFetchInterval = 43200;

/// Label for serial queue for read/write lock on ivars.
static const char *RCNRemoteConfigQueueLabel = "com.google.GoogleConfigService.FIRRemoteConfig";

/// Constants for key names in the fetch response.
/// Key that includes an array of template entries.
static NSString *const RCNFetchResponseKeyEntries = @"entries";
/// Key that includes data for experiment descriptions in ABT.
static NSString *const RCNFetchResponseKeyExperimentDescriptions = @"experimentDescriptions";
/// Error key.
static NSString *const RCNFetchResponseKeyError = @"error";
/// Error code.
static NSString *const RCNFetchResponseKeyErrorCode = @"code";
/// Error status.
static NSString *const RCNFetchResponseKeyErrorStatus = @"status";
/// Error message.
static NSString *const RCNFetchResponseKeyErrorMessage = @"message";
/// The current state of the backend template.
static NSString *const RCNFetchResponseKeyState = @"state";
/// Default state (when not set).
static NSString *const RCNFetchResponseKeyStateUnspecified = @"INSTANCE_STATE_UNSPECIFIED";
/// Config key/value map and/or ABT experiment list differs from last fetch.
/// TODO(mandard): Migrate to the new HTTP error codes once available in the backend. b/117182055
static NSString *const RCNFetchResponseKeyStateUpdate = @"UPDATE";
/// No template fetched.
static NSString *const RCNFetchResponseKeyStateNoTemplate = @"NO_TEMPLATE";
/// Config key/value map and ABT experiment list both match last fetch.
static NSString *const RCNFetchResponseKeyStateNoChange = @"NO_CHANGE";
/// Template found, but evaluates to empty (e.g. all keys omitted).
static NSString *const RCNFetchResponseKeyStateEmptyConfig = @"EMPTY_CONFIG";
/// Key that includes data for active rollouts that this client is a part of.
static NSString *const RCNFetchResponseKeyActiveRollouts = @"activeRollouts";
/// Key that includes data for active rollouts assigned for this client.
static NSString *const RCNFetchResponseKeyEnabledFeatures = @"enabledFeatureKeys";
/// The rollout identifier key for rollouts information sent from the backend.
static NSString *const RCNRolloutIdentifierKey = @"rollout";
/// The feature enabled key for rollouts information sent from the backend.
static NSString *const RCNRolloutFeatureEnabledKey = @"featureEnabled";
