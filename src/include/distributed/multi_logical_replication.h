/*-------------------------------------------------------------------------
 *
 * multi_logical_replication.h
 *
 *    Declarations for public functions and variables used in logical replication
 *    on the distributed tables while moving shards.
 *
 * Copyright (c) 2017, Citus Data, Inc.
 *
 *-------------------------------------------------------------------------
 */
#ifndef MULTI_LOGICAL_REPLICATION_H_
#define MULTI_LOGICAL_REPLICATION_H_


#include "nodes/pg_list.h"


/* Config variables managed via guc.c */
extern int LogicalReplicationTimeout;

extern bool PlacementMovedUsingLogicalReplicationInTX;


extern void LogicallyReplicateShards(List *shardList, char *sourceNodeName,
									 int sourceNodePort, char *targetNodeName,
									 int targetNodePort);

extern void ConflictOnlyWithIsolationTesting(void);
extern void CreateReplicaIdentity(List *shardList, char *nodeName, int32
								  nodePort);
extern XLogRecPtr GetRemoteLogPosition(MultiConnection *connection);
extern List * GetQueryResultStringList(MultiConnection *connection, char *query);

extern void DropShardSubscription(MultiConnection *connection,
								  char *subscriptionName);
extern void DropShardPublication(MultiConnection *connection, char *publicationName);

extern void DropShardUser(MultiConnection *connection, char *username);
extern void DropShardReplicationSlot(MultiConnection *connection,
									 char *publicationName);


extern char * ShardSubscriptionRole(Oid ownerId, char *operationPrefix);
extern char * ShardSubscriptionName(Oid ownerId, char *operationPrefix);
extern void CreateShardSplitSubscription(MultiConnection *connection,
										 char *sourceNodeName,
										 int sourceNodePort, char *userName,
										 char *databaseName,
										 char *publicationName, char *slotName,
										 Oid ownerId);

extern void WaitForRelationSubscriptionsBecomeReady(MultiConnection *targetConnection,
													Bitmapset *tableOwnerIds,
													char *operationPrefix);
extern void WaitForShardSubscriptionToCatchUp(MultiConnection *targetConnection,
											  XLogRecPtr sourcePosition,
											  Bitmapset *tableOwnerIds,
											  char *operationPrefix);

#define SHARD_MOVE_PUBLICATION_PREFIX "citus_shard_move_publication_"
#define SHARD_MOVE_SUBSCRIPTION_ROLE_PREFIX "citus_shard_move_subscription_role_"
#define SHARD_MOVE_SUBSCRIPTION_PREFIX "citus_shard_move_subscription_"
#define SHARD_SPLIT_PUBLICATION_PREFIX "citus_shard_split_publication_"
#define SHARD_SPLIT_SUBSCRIPTION_PREFIX "citus_shard_split_subscription_"
#define SHARD_SPLIT_SUBSCRIPTION_ROLE_PREFIX "citus_shard_split_subscription_role_"
#define SHARD_SPLIT_TEMPLATE_REPLICATION_SLOT_PREFIX "citus_shard_split_template_slot_"
#define SHARD_SPLIT_REPLICATION_SLOT_PREFIX "citus_shard_split_"
#endif /* MULTI_LOGICAL_REPLICATION_H_ */
