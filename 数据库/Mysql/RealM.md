# realm

## 迁移数据

### Local migrations

Local migrations are defined by setting Realm.Configuration.schemaVersion and Realm.Configuration.migrationBlock. Your migration block provides all the logic for converting data models from previous schemas to the new schema. When creating a Realm with this configuration, the migration block will be applied to update the Realm to the given schema version if a migration is needed.

Suppose we want to migrate the Person model declared earlier. The minimal necessary migration block would be the following:

``` Swift
// Inside your application(application:didFinishLaunchingWithOptions:)

let config = Realm.Configuration(
    // Set the new schema version. This must be greater than the previously used
    // version (if you've never set a schema version before, the version is 0).
    schemaVersion: 1,

    // Set the block which will be called automatically when opening a Realm with
    // a schema version lower than the one set above
    migrationBlock: { migration, oldSchemaVersion in
        // We haven’t migrated anything yet, so oldSchemaVersion == 0
        if (oldSchemaVersion < 1) {
            // Nothing to do!
            // Realm will automatically detect new properties and removed properties
            // And will update the schema on disk automatically
        }
    })

// Tell Realm to use this new configuration object for the default Realm
Realm.Configuration.defaultConfiguration = config

// Now that we've told Realm how to handle the schema change, opening the file
// will automatically perform the migration
let realm = try! Realm()
```
At the very minimum we need to update the version with an empty block to indicate that the schema has been upgraded (automatically) by Realm.

### Updating values
While this is the minimum acceptable migration, we probably want to use this block to populate any new properties (in this case fullName) with something meaningful. Within the migration block we can call Migration().enumerateObjects(ofType: _:_:) to enumerate each Object of a certain type, and apply any necessary migration logic. Notice how for each enumeration the existing Object instance is accessed via an oldObject variable and the updated instance is accessed via newObject:

``` Swift
// Inside your application(application:didFinishLaunchingWithOptions:)

Realm.Configuration.defaultConfiguration = Realm.Configuration(
    schemaVersion: 1,
    migrationBlock: { migration, oldSchemaVersion in
        if (oldSchemaVersion < 1) {
            // The enumerateObjects(ofType:_:) method iterates
            // over every Person object stored in the Realm file
            migration.enumerateObjects(ofType: Person.className()) { oldObject, newObject in
                // combine name fields into a single field
                let firstName = oldObject!["firstName"] as! String
                let lastName = oldObject!["lastName"] as! String
                newObject!["fullName"] = "\(firstName) \(lastName)"
            }
        }
    })
```
Once the migration is successfully completed, the Realm and all of its objects can be accessed as usual by your app.

Renaming properties
Renaming the property on a class as part of a migration is more efficient than copying values and preserves relationships rather than duplicating them.

To rename a property during a migration, make sure that your new models have a property with the new name and don’t have a property with the old name.

If the new property has different nullability or indexing settings, those will be applied during the rename operation.

Here’s how you could rename Person’s yearsSinceBirth property to age:

```Swift
// Inside your application(application:didFinishLaunchingWithOptions:)

Realm.Configuration.defaultConfiguration = Realm.Configuration(
    schemaVersion: 1,
    migrationBlock: { migration, oldSchemaVersion in
        // We haven’t migrated anything yet, so oldSchemaVersion == 0
        if (oldSchemaVersion < 1) {
            // The renaming operation should be done outside of calls to `enumerateObjects(ofType: _:)`.
            migration.renameProperty(onType: Person.className(), from: "yearsSinceBirth", to: "age")
        }
    })
```
### Linear migrations
Suppose we have two users for our app: JP and Tim. JP updates the app very often, but Tim happens to skip a few versions. It’s likely that JP has seen every new version of our app, and every schema upgrade in order: he downloaded a version of the app that took him from v0 to v1, and later another update that took him from v1 to v2. In contrast, it’s possible that Tim might download an update of the app that will need to take him from v0 to v2 immediately. Structuring your migration blocks with non-nested if (oldSchemaVersion < X) calls ensures that they will see all necessary upgrades, no matter which schema version they start from.

Another scenario may arise in the case of users who skipped versions of your app. If you delete a property email at version 2 and re-introduce it at version 3, and a user jumps from version 1 to version 3, Realm will not be able to automatically detect the deletion of the email property, as there will be no mismatch between the schema on disk and the schema in the code for that property. This will lead to Tim’s Person object having a v3 address property that has the contents of the v1 address property. This may not be a problem, unless you changed the internal storage representation of that property between v1 and v3 (say, went from an ISO address representation to a custom one). To avoid this, we recommend you nil out the email property on the if (oldSchemaVersion < 3) statement, guaranteeing that all Realms upgraded to version 3 will have a correct dataset.

[迁移文档](https://realm.io/docs/swift/latest/#migrations)