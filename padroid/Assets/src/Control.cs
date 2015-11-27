using UnityEngine;
using UnityEngine.EventSystems;
using System.Collections;

public class Control : EventTrigger {
	public RectTransform RectTransform {
		get {
			return GetComponent<RectTransform>();
		}
	}

	public Vector2 Size {
		get {
			return RectTransform.rect.size;
		}
	}

	public event PointerEventHandler UiBeginDrag;
	public override void OnBeginDrag(PointerEventData eventData) {
		if (UiBeginDrag != null)
			UiBeginDrag(this, eventData);
	}

	public event BaseEventHandler UiCancel;
	public override void OnCancel(BaseEventData eventData) {
		if (UiCancel != null)
            UiCancel(this, eventData);
	}

	public event PointerEventHandler UiDrag;
	public override void OnDrag(PointerEventData eventData) {
		if (UiDrag != null)
            UiDrag(this, eventData);
	}

	public event PointerEventHandler UiDrop;
	public override void OnDrop(PointerEventData eventData) {
		if (UiDrop != null)
            UiDrop(this, eventData);
	}

	public event PointerEventHandler UiEndDrag;
	public override void OnEndDrag(PointerEventData eventData) {
		if (UiEndDrag != null)
            UiEndDrag(this, eventData);
	}

	public event AxisEventHandler UiMove;
	public override void OnMove(AxisEventData eventData) {
		if (UiMove != null)
            UiMove(this, eventData);
	}

	public event PointerEventHandler UiPointerClick;
	public override void OnPointerClick(PointerEventData eventData) {
		if (UiPointerClick != null)
            UiPointerClick(this, eventData);
	}

	public event PointerEventHandler UiPointerDown;
	public override void OnPointerDown(PointerEventData eventData) {
        pointerDownTimeStamp = Time.realtimeSinceStartup;

        pointerDown = true;

		if (UiPointerDown != null)
            UiPointerDown(this, eventData);
	}

	public event PointerEventHandler UiPointerEnter;
	public override void OnPointerEnter(PointerEventData eventData) {
		if (UiPointerEnter != null)
            UiPointerEnter(this, eventData);
	}

	public event PointerEventHandler UiPointerExit;
	public override void OnPointerExit(PointerEventData eventData) {
		if (UiPointerExit != null)
            UiPointerExit(this, eventData);
	}

	public event PointerEventHandler UiPointerUp;
	public override void OnPointerUp(PointerEventData eventData) {
        pointerDown = false;

		if (UiPointerUp != null)
            UiPointerUp(this, eventData);
	}

    private float hoverTime = 0.6f;
    private float pointerDownTimeStamp = float.NaN;
    private bool pointerDown = false;
    public event CommonEventHandler UiPointerHover;
    protected virtual void Update() {
        if (pointerDown) {
            if (Time.realtimeSinceStartup - pointerDownTimeStamp >= hoverTime) {
                pointerDownTimeStamp = float.MinValue;

                if (UiPointerHover != null)
                    UiPointerHover(this);
            }
        }
	}
}

public delegate void BaseEventHandler(Control control, BaseEventData eventData);
public delegate void PointerEventHandler(Control control, PointerEventData eventData);
public delegate void AxisEventHandler(Control control, AxisEventData eventData);
public delegate void CommonEventHandler(Control control);
