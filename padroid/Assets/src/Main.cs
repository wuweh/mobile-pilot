using UnityEngine;
using UnityEngine.EventSystems;
using System.Collections;
using System.Runtime.InteropServices;

public class Main : MonoBehaviour {
#if UNITY_EDITOR
    private static void bl_open() {
    }
    private static void bl_close() {
    }
    private static void bl_connect() {
    }
    private static void bl_send(string msg) {
        print(msg);
    }

    private static void bl_msg_box(string title, string message) {
    }
#else
    [DllImport("__Internal")]
    private static extern void bl_open();
    [DllImport("__Internal")]
    private static extern void bl_close();
    [DllImport("__Internal")]
    private static extern void bl_connect();
    [DllImport("__Internal")]
    private static extern void bl_send(string msg);

    [DllImport("__Internal")]
    private static extern void bl_msg_box(string title, string message);
#endif

    public Control left = null;
    public Control right = null;
    public Control select = null;
    public Control start = null;

    private Vector2? leftData = null;
    private Vector2? rightData = null;

    private float leftTimeStamp = 0.0f;
    private float rightTimeStamp = 0.0f;

    private void Awake() {
        bl_open();
    }

    private void OnDestroy() {
        bl_close();
    }

	public void OnApplicationPause(bool p) {
		if (!p)
			bl_connect();
	}

	private void Start() {
        //bl_connect();

        left.UiPointerDown += OnLeftDown;
        left.UiPointerUp += OnLeftUp;
        left.UiDrag += OnLeftDrag;

        right.UiPointerDown += OnRightDown;
        right.UiPointerUp += OnRightUp;
        right.UiDrag += OnRightDrag;

        select.UiPointerDown += OnSelectDown;
        select.UiPointerUp += OnSelectUp;

        start.UiPointerDown += OnStartDown;
        start.UiPointerUp += OnStartUp;
	}

	private void Update() {
		float interval = leftData != null && rightData != null ? 10.0f : 18.0f;

        if (leftData == null) {
            if (Time.realtimeSinceStartup - leftTimeStamp > 1.0f) {
                leftTimeStamp = Time.realtimeSinceStartup;
                OnLeftUp(null, null);
            }
        } else {
			if (Time.realtimeSinceStartup - leftTimeStamp > 1.0f / interval) {
				leftTimeStamp = Time.realtimeSinceStartup;
            	Send("<" + ((int)leftData.Value.x).ToString() + "," + ((int)leftData.Value.y).ToString());
			}
        }

        if (rightData == null) {
            if (Time.realtimeSinceStartup - rightTimeStamp > 1.0f) {
                rightTimeStamp = Time.realtimeSinceStartup;
                OnRightUp(null, null);
            }
        } else {
			if (Time.realtimeSinceStartup - rightTimeStamp > 1.0f / interval) {
				rightTimeStamp = Time.realtimeSinceStartup;
	            Send(">" + ((int)rightData.Value.x).ToString() + "," + ((int)rightData.Value.y).ToString());
			}
        }
	}

    private void Send(string msg) {
        bl_send(msg + ";");
    }
	
	private void OnLeftDown(Control control, PointerEventData eventData) {
        leftData = new Vector2(0.0f, 0.0f);

        Send("ld");
	}

    private void OnLeftUp(Control control, PointerEventData eventData) {
        leftData = null;

        Send("lu");
    }

    private void OnLeftDrag(Control control, PointerEventData eventData) {
        Vector2 prs = eventData.pressPosition;
        Vector2 now = eventData.position;
        Vector2 size = left.Size;
        Vector2 data = new Vector2(
            Mathf.Clamp((now.x - prs.x) / (size.x / 2.0f) * 255.0f, -255.0f, 255.0f),
            Mathf.Clamp((now.y - prs.y) / (size.y / 2.0f) * 255.0f, -255.0f, 255.0f)
        );

        leftData = new Vector2(data.x, data.y);
    }

    private void OnRightDown(Control control, PointerEventData eventData) {
        rightData = new Vector2(0.0f, 0.0f);

        Send("rd");
	}

    private void OnRightUp(Control control, PointerEventData eventData) {
        rightData = null;

        Send("ru");
    }

    private void OnRightDrag(Control control, PointerEventData eventData) {
        Vector2 prs = eventData.pressPosition;
        Vector2 now = eventData.position;
        Vector2 size = right.Size;
        Vector2 data = new Vector2(
            Mathf.Clamp((now.x - prs.x) / (size.x / 2.0f) * 255.0f, -255.0f, 255.0f),
            Mathf.Clamp((now.y - prs.y) / (size.y / 2.0f) * 255.0f, -255.0f, 255.0f)
        );

        rightData = new Vector2(data.x, data.y);
    }

    private void OnSelectDown(Control control, PointerEventData eventData) {
        Send("sd");
	}

    private void OnSelectUp(Control control, PointerEventData eventData) {
        Send("su");
    }

    private void OnStartDown(Control control, PointerEventData eventData) {
        Send("td");
	}

    private void OnStartUp(Control control, PointerEventData eventData) {
        Send("tu");
    }
}
