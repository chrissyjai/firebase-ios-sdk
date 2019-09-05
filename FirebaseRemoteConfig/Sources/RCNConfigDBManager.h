#import <Foundation/Foundation.h>

#import "googlemac/iPhone/Config/RemoteConfig/Source/RCNConfigContent.h"

typedef NS_ENUM(NSInteger, RCNUpdateOption) {
  RCNUpdateOptionApplyTime,
  RCNUpdateOptionDefaultTime,
  RCNUpdateOptionFetchStatus,
};

/// Column names in metadata table
static NSString *const RCNKeyBundleIdentifier = @"bundle_identifier";
static NSString *const RCNKeyFetchTime = @"fetch_time";
static NSString *const RCNKeyDigestPerNamespace = @"digest_per_ns";
static NSString *const RCNKeyDeviceContext = @"device_context";
static NSString *const RCNKeyAppContext = @"app_context";
static NSString *const RCNKeySuccessFetchTime = @"success_fetch_time";
static NSString *const RCNKeyFailureFetchTime = @"failure_fetch_time";
static NSString *const RCNKeyLastFetchStatus = @"last_fetch_status";
static NSString *const RCNKeyLastFetchError = @"last_fetch_error";
static NSString *const RCNKeyLastApplyTime = @"last_apply_time";
static NSString *const RCNKeyLastSetDefaultsTime = @"last_set_defaults_time";
/// The name of the features key to store in the database.
static NSString *const kRCNFeaturesKeyName = @"features";
static NSString *const kRCNRolloutsKeyName = @"rollouts";

/// Persist config data in sqlite database on device. Managing data read/write from/to database.
@interface RCNConfigDBManager : NSObject
/// Shared Singleton Instance
+ (instancetype)sharedInstance;

/// Database Operation Completion callback.
/// @param success Decide whether the DB operation succeeds.
/// @param result  Return operation result data.
typedef void (^RCNDBCompletion)(BOOL success, NSDictionary *result);

/// Database Load Operation Completion callback.
/// @param success Decide whether the DB operation succeeds.
/// @param fetchedConfig  Return fetchedConfig loaded from DB
/// @param activeConfig  Return activeConfig loaded from DB
/// @param defaultConfig  Return defaultConfig loaded from DB
typedef void (^RCNDBLoadCompletion)(BOOL success, NSDictionary *fetchedConfig,
                                    NSDictionary *activeConfig, NSDictionary *defaultConfig,
                                    NSDictionary<NSString *, id> *fetchedFeaturesAndRollouts,
                                    NSDictionary<NSString *, id> *activatedFeaturesAndRollouts);

/// Returns the current version of the Remote Config database.
+ (NSString *)remoteConfigPathForDatabase;

/// Load config content from main table and feature information from feature table to cached memory
/// during app start.
- (void)loadWithBundleIdentifier:(NSString *)bundleIdentifier
               completionHandler:(RCNDBLoadCompletion)handler;
/// Load config settings from metadata table to cached memory during app start. Config settings
/// include success/failure fetch times, device contenxt, app context, etc.
- (NSDictionary *)loadMetadataWithBundleIdentifier:(NSString *)bundleIdentifier;
/// Load internal metadata from internal metadata table, such as customized HTTP connection/read
/// timeout, throttling time interval and number limit of throttling, etc.
/// This call needs to be blocking to ensure throttling works during apps starts.
- (NSDictionary *)loadInternalMetadataTable;
/// Load experiment from experiment table.
/// @param handler    The callback when reading from DB is complete.
- (void)loadExperimentWithCompletionHandler:(RCNDBCompletion)handler;

/// Insert a record in metadata table.
/// @param columnNameToValue The column name and its value to be inserted in metadata table.
/// @param handler           The callback.
- (void)insertMetadataTableWithValues:(NSDictionary *)columnNameToValue
                    completionHandler:(RCNDBCompletion)handler;
/// Insert a record in main table.
/// @param values Values to be inserted.
- (void)insertMainTableWithValues:(NSArray *)values
                       fromSource:(RCNDBSource)source
                completionHandler:(RCNDBCompletion)handler;
/// Insert a record in features table.
/// @param values Values to be inserted.
- (void)insertFeaturesTableWithValues:(NSArray<id> *)values
                           fromSource:(RCNDBSource)source
                    completionHandler:(RCNDBCompletion)handler;
/// Insert a record in internal metadata table.
/// @param values Values to be inserted.
- (void)insertInternalMetadataTableWithValues:(NSArray *)values
                            completionHandler:(RCNDBCompletion)handler;
/// Insert exepriment data in experiment table.
/// @param key        The key of experiment data belongs to, which are defined in
///                   RCNConfigDefines.h.
/// @param value      The value that experiment.
/// @param handler    The callback.
- (void)insertExperimentTableWithKey:(NSString *)key
                               value:(NSData *)value
                   completionHandler:(RCNDBCompletion)handler;

- (void)updateMetadataWithOption:(RCNUpdateOption)option
                          values:(NSArray *)values
               completionHandler:(RCNDBCompletion)handler;
/// Clear the record of given namespace and package name
/// before updating the table.
- (void)deleteRecordFromMainTableWithNamespace:(NSString *)namespace_p
                              bundleIdentifier:(NSString *)bundleIdentifier
                                    fromSource:(RCNDBSource)source;
/// Clear the record of given namespace and package name
/// before updating the table.
- (void)deleteRecordFromFeaturesTableWithNamespace:(NSString *)namespace_p
                                  bundleIdentifier:(NSString *)bundleIdentifier
                                        fromSource:(RCNDBSource)source;
/// Remove all the records of given package name from metadata/internal metadata DB before updating
/// new values from response.
- (void)deleteRecordWithBundleIdentifier:(NSString *)bundlerIdentifier
                            isInternalDB:(BOOL)isInternalDB;
/// Remove all the records from a config content table.
- (void)deleteAllRecordsFromTableWithSource:(RCNDBSource)source;

/// Remove all the records from features table.
- (void)deleteAllRecordsFromFeaturesTableWithSource:(RCNDBSource)source;

/// Remove all the records from experiment table with given key.
/// @param key  The key of experiment data belongs to, which are defined in RCNConfigDefines.h.
- (void)deleteExperimentTableForKey:(NSString *)key;
@end
