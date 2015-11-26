#import <UIKit/UIKit.h>
#import "DFBlunoManager.h"

@interface BlunoImpl : NSObject<DFBlunoDelegate> //NSObject<MFMailComposeViewControllerDelegate>

@property (strong, nonatomic) DFBlunoManager* blunoManager;
@property (strong, nonatomic) DFBlunoDevice* blunoDev;
@property (strong, nonatomic) NSMutableArray* aryDevices;

//@property (weak, nonatomic) IBOutlet UILabel* lbReceivedMsg;
//@property (weak, nonatomic) IBOutlet UITextField* txtSendMsg;
//@property (weak, nonatomic) IBOutlet UILabel* lbReady;

//@property (strong, nonatomic) IBOutlet UIView* viewDevices;
//@property (weak, nonatomic) IBOutlet UITableView* tbDevices;

//@property (weak, nonatomic) IBOutlet UIActivityIndicatorView* SearchIndicator;
//@property (strong, nonatomic) IBOutlet UITableViewCell* cellDevices;

- (void) open;
- (void) close;

- (void) connect;

- (void) send : (NSString*) msg;

- (IBAction) actionSearch : (id) sender;
- (IBAction) actionReturn : (id) sender;
- (IBAction) actionSend : (id) sender;
- (IBAction) actionDidEnd : (id) sender;

@end
